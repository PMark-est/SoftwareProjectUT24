import base64
import binascii
import os
import random
import uuid
import zlib
import json
import re


from collections import defaultdict, OrderedDict
from concurrent import futures
from concurrent.futures import ThreadPoolExecutor

from flask import Blueprint
from flask import current_app as app

from korp import utils
from korp.cwb import cwb
from korp.memcached import memcached

bp = Blueprint("query", __name__)


@bp.route("/query_sample", methods=["GET", "POST"])
@utils.main_handler
@utils.prevent_timeout
def query_sample(args):
    """Run a sequential query in the selected corpora in random order until at least one
    hit is found, and then abort the query. Use to get a random sample sentence."""

    corpora = utils.parse_corpora(args)
    # Randomize corpus order
    random.shuffle(corpora)

    for i in range(len(corpora)):
        corpus = corpora[i]
        utils.check_authorization([corpus])

        args["corpus"] = corpus
        args["sort"] = "random"

        result = utils.generator_to_dict(query(args))
        if result["hits"] > 0:
            yield result
            return

    yield result


@bp.route("/query", methods=["GET", "POST"])
@utils.main_handler
@utils.prevent_timeout
def query(args, abort_event=None):
    """Perform a CQP query and return a number of matches."""
    utils.assert_key("cqp", args, r"", True)
    utils.assert_key("corpus", args, utils.IS_IDENT, True)
    utils.assert_key("start", args, utils.IS_NUMBER)
    utils.assert_key("end", args, utils.IS_NUMBER)
    # utils.assert_key("context", args, r"^\d+ [\w-]+$")
    utils.assert_key("show", args, utils.IS_IDENT)
    utils.assert_key("show_struct", args, utils.IS_IDENT)
    # utils.assert_key("within", args, utils.IS_IDENT)
    utils.assert_key("cut", args, utils.IS_NUMBER)
    utils.assert_key("sort", args, r"")
    utils.assert_key("incremental", args, r"(true|false)")

    incremental = utils.parse_bool(args, "incremental", False)
    free_search = not utils.parse_bool(args, "in_order", True)
    use_cache = args["cache"]
    cut = args.get("cut")

    corpora = utils.parse_corpora(args)

    utils.check_authorization(corpora)

    show = args.get("show") or []  # We don't use .get("show", []) since "show" might be the empty string.
    if isinstance(show, str):
        show = show.split(utils.QUERY_DELIM)
    show = set(show + ["word"])

    show_structs = args.get("show_struct") or []
    if isinstance(show_structs, str):
        show_structs = show_structs.split(utils.QUERY_DELIM)
    show_structs = set(show_structs)

    expand_prequeries = utils.parse_bool(args, "expand_prequeries", True)

    start, end = int(args.get("start") or 0), int(args.get("end") or 9)

    if app.config["MAX_KWIC_ROWS"] and end - start >= app.config["MAX_KWIC_ROWS"]:
        raise ValueError("At most %d KWIC rows can be returned per call." % app.config["MAX_KWIC_ROWS"])

    within = utils.parse_within(args)

    # Parse "context"/"left_context"/"right_context"/"default_context"
    default_context = args.get("default_context") or "10 words"
    context = defaultdict(lambda: (default_context,))
    contexts = {}

    for c in ("left_context", "right_context", "context"):
        cv = args.get(c, "")
        if cv:
            if ":" not in cv:
                raise ValueError("Malformed value for key '%s'." % c)
            contexts[c] = {x.split(":")[0].upper(): x.split(":")[1] for x in cv.split(utils.QUERY_DELIM)}
        else:
            contexts[c] = {}

    for corpus in set(k for v in contexts.values() for k in v.keys()):
        if corpus in contexts["left_context"] or corpus in contexts["right_context"]:
            context[corpus] = (contexts["left_context"].get(corpus, default_context),
                               contexts["right_context"].get(corpus, default_context))
        else:
            context[corpus] = (contexts["context"].get(corpus, default_context),)

    sort = args.get("sort")
    sort_random_seed = args.get("random_seed")

    # Sort numbered CQP-queries numerically
    cqp, _ = utils.parse_cqp_subcqp(args)

    if len(cqp) > 1 and expand_prequeries and not all(within[c] for c in corpora):
        raise ValueError("Multiple CQP queries requires 'within' or 'expand_prequeries=false'")

    # Parameters used for all queries
    queryparams = {"free_search": free_search,
                   "use_cache": use_cache,
                   "cache_dir": app.config["CACHE_DIR"],
                   "cache_max_query_data": app.config.get("CACHE_MAX_QUERY_DATA"),
                   "show": show,
                   "show_structs": show_structs,
                   "expand_prequeries": expand_prequeries,
                   "cut": cut,
                   "cqp": cqp,
                   "sort": sort,
                   "random_seed": sort_random_seed
                   }

    result = {"kwic": []}

    # Checksum for whole query, used to verify 'query_data' from the client
    checksum = utils.get_hash((sorted(corpora),
                              cqp,
                              sorted(within.items()),
                              cut,
                              expand_prequeries,
                              free_search))

    debug = {}
    if "debug" in args:
        debug["checksum"] = checksum

    ns = utils.Namespace()
    ns.total_hits = 0
    statistics = {}

    saved_statistics = {}
    query_data = args.get("query_data")
    if query_data:
        try:
            query_data = zlib.decompress(base64.b64decode(
                query_data.replace("\\n", "\n").replace("-", "+").replace("_", "/"))).decode("UTF-8")
        except:
            if "debug" in args:
                debug["query_data_unparseable"] = True
        else:
            if "debug" in args:
                debug["query_data_read"] = True
            saved_checksum, stats_temp = query_data.split(";", 1)
            if saved_checksum == checksum:
                for pair in stats_temp.split(";"):
                    corpus, hits = pair.split(":")
                    saved_statistics[corpus] = int(hits)
            elif "debug" in args:
                debug["query_data_checksum_mismatch"] = True

    if use_cache and not saved_statistics:
        memcached_keys = {}
        # Query data parsing failed or was missing, so look for cached hits instead
        with memcached.get_client() as mc:
            cache_prefixes = utils.cache_prefix(mc, [corpus.split("|")[0] for corpus in corpora])
            for corpus in corpora:
                corpus_checksum = utils.get_hash((cqp,
                                                 within[corpus],
                                                 cut,
                                                 expand_prequeries,
                                                 free_search))
                memcached_keys["%s:query_size_%s" % (cache_prefixes[corpus.split("|")[0]], corpus_checksum)] = corpus

            cached_corpus_hits = mc.get_many(memcached_keys.keys())
        for key in cached_corpus_hits:
            saved_statistics[memcached_keys[key]] = cached_corpus_hits[key]

    ns.start_local = start
    ns.end_local = end

    if saved_statistics:
        if "debug" in args:
            debug["cache_coverage"] = "%d/%d" % (len(saved_statistics), len(corpora))
        complete_hits = set(corpora) == set(saved_statistics.keys())
    else:
        complete_hits = False

    if abort_event and abort_event.is_set():
        return

    if complete_hits:
        # We have saved_statistics available for all corpora, so calculate which
        # corpora need to be queried and then query them in parallel.
        corpora_hits = which_hits(corpora, saved_statistics, start, end)
        ns.total_hits = sum(saved_statistics.values())
        statistics = saved_statistics
        corpora_kwics = {}
        ns.progress_count = 0

        if len(corpora_hits) == 0:
            pass
        elif len(corpora_hits) == 1:
            # If only hits in one corpus, it is faster to not use threads
            corpus, hits = list(corpora_hits.items())[0]
            result["kwic"], _ = query_and_parse(corpus, within=within[corpus], context=context[corpus],
                                                start=hits[0], end=hits[1], abort_event=abort_event, **queryparams)
        else:
            if incremental:
                yield {"progress_corpora": list(corpora_hits.keys())}

            with ThreadPoolExecutor(max_workers=app.config["PARALLEL_THREADS"]) as executor:
                future_query = dict(
                    (executor.submit(query_and_parse, corpus, within=within[corpus], context=context[corpus],
                                     start=corpora_hits[corpus][0], end=corpora_hits[corpus][1],
                                     abort_event=abort_event, **queryparams),
                     corpus)
                    for corpus in corpora_hits)

                for future in futures.as_completed(future_query):
                    if abort_event and abort_event.is_set():
                        for f in future_query:
                            f.cancel()
                        return
                    corpus = future_query[future]
                    if future.exception() is not None:
                        raise utils.CQPError(future.exception())
                    else:
                        kwic, _ = future.result()
                        corpora_kwics[corpus] = kwic
                        if incremental:
                            yield {"progress_%d" % ns.progress_count: {"corpus": corpus,
                                                                       "hits": corpora_hits[corpus][1] -
                                                                       corpora_hits[corpus][0] + 1}}
                            ns.progress_count += 1

            for corpus in corpora:
                if corpus in corpora_hits.keys():
                    result["kwic"].extend(corpora_kwics[corpus])
    else:
        # saved_statistics is missing or incomplete, so we need to query the corpora in
        # serial until we have the needed rows, and then query the remaining corpora
        # in parallel to get number of hits.
        if incremental:
            yield {"progress_corpora": corpora}
        ns.progress_count = 0
        ns.rest_corpora = []

        # Serial until we've got all the requested rows
        for i, corpus in enumerate(corpora):
            if abort_event and abort_event.is_set():
                return
            if ns.end_local < 0:
                ns.rest_corpora = corpora[i:]
                break
            skip_corpus = False
            if corpus in saved_statistics:
                nr_hits = saved_statistics[corpus]
                if nr_hits - 1 < ns.start_local:
                    kwic = []
                    skip_corpus = True

            if not skip_corpus:
                kwic, nr_hits = query_and_parse(corpus, within=within[corpus], context=context[corpus],
                                                start=ns.start_local, end=ns.end_local, abort_event=abort_event,
                                                **queryparams)

            statistics[corpus] = nr_hits
            ns.total_hits += nr_hits

            # Calculate which hits from next corpus we need, if any
            ns.start_local -= nr_hits
            ns.end_local -= nr_hits
            if ns.start_local < 0:
                ns.start_local = 0

            result["kwic"].extend(kwic)

            if incremental:
                yield {"progress_%d" % ns.progress_count: {"corpus": corpus, "hits": nr_hits}}
                ns.progress_count += 1

        if incremental:
            yield result
            result = {}

        if ns.rest_corpora:
            if saved_statistics:
                for corpus in ns.rest_corpora:
                    if corpus in saved_statistics:
                        statistics[corpus] = saved_statistics[corpus]
                        ns.total_hits += saved_statistics[corpus]

            with ThreadPoolExecutor(max_workers=app.config["PARALLEL_THREADS"]) as executor:
                future_query = dict(
                    (executor.submit(query_corpus, corpus, within=within[corpus],
                                     context=context[corpus], start=0, end=0, no_results=True, abort_event=abort_event,
                                     **queryparams),
                     corpus)
                    for corpus in ns.rest_corpora if corpus not in saved_statistics)

                for future in futures.as_completed(future_query):
                    if abort_event and abort_event.is_set():
                        for f in future_query:
                            f.cancel()
                        return
                    corpus = future_query[future]
                    if future.exception() is not None:
                        raise utils.CQPError(future.exception())
                    else:
                        _, nr_hits, _ = future.result()
                        statistics[corpus] = nr_hits
                        ns.total_hits += nr_hits
                        if incremental:
                            yield {"progress_%d" % ns.progress_count: {"corpus": corpus, "hits": nr_hits}}
                            ns.progress_count += 1

    if "debug" in args:
        debug["cqp"] = cqp

    result["hits"] = ns.total_hits
    result["corpus_hits"] = statistics
    result["corpus_order"] = corpora
    result["query_data"] = binascii.b2a_base64(zlib.compress(
        bytes(checksum + ";" + ";".join("%s:%d" % (c, h) for c, h in statistics.items()),
              "utf-8"))).decode("utf-8").replace("+", "-").replace("/", "_")

    if debug:
        result["DEBUG"] = debug

    yield result


def query_corpus(corpus, cqp, within=None, cut=None, context=None, show=None, show_structs=None, start=0, end=10,
                 sort=None, random_seed=None,
                 no_results=False, expand_prequeries=True, free_search=False, use_cache=False, cache_dir=None,
                 cache_max_query_data=0, abort_event=None):
    if use_cache:
        # Calculate checksum
        # Needs to contain all arguments that may influence the results
        checksum_data = (cqp,
                         within,
                         cut,
                         expand_prequeries,
                         free_search)

        checksum = utils.get_hash(checksum_data)
        unique_id = str(uuid.uuid4())

        cache_query = "query_data_%s" % checksum
        cache_query_temp = cache_query + "_" + unique_id

        cache_filename = os.path.join(cache_dir, "%s:query_data_%s" % (corpus.split("|")[0], checksum))
        cache_filename_temp = cache_filename + "_" + unique_id

        with memcached.get_client() as mc:
            cache_size_key = "%s:query_size_%s" % (utils.cache_prefix(mc, corpus.split("|")[0]), checksum)
            cache_hits = mc.get(cache_size_key)
        is_cached = cache_hits is not None and os.path.isfile(cache_filename)
        cached_no_hits = cache_hits == 0
    else:
        is_cached = False

    # Optimization
    do_optimize = True

    show = show.copy()  # To not edit the original

    cqpparams = {"within": within,
                 "cut": cut}

    # Handle aligned corpora
    if "|" in corpus:
        linked = corpus.split("|")
        cqpnew = []

        for c in cqp:
            cs = c.split("LINKED_CORPUS:")

            # In a multi-language query, the "within" argument must be placed directly
            # after the main (first language) query
            if len(cs) > 1 and within:
                cs[0] = "%s within %s : " % (cs[0].rstrip()[:-1], within)
                del cqpparams["within"]

            c = [cs[0]]

            for d in cs[1:]:
                linked_corpora, link_cqp = d.split(None, 1)
                if linked[1] in linked_corpora.split("|"):
                    c.append("%s %s" % (linked[1], link_cqp))

            cqpnew.append("".join(c).rstrip(": "))

        cqp = cqpnew
        corpus = linked[0]
        show.add(linked[1].lower())

    # Sorting
    if sort == "left":
        sortcmd = ["sort by word on match[-1] .. match[-3];"]
    elif sort == "keyword":
        sortcmd = ["sort by word;"]
    elif sort == "right":
        sortcmd = ["sort by word on matchend[1] .. matchend[3];"]
    elif sort == "random":
        sortcmd = ["sort randomize %s;" % (random_seed or "")]
    elif sort:
        # Sort by positional attribute
        sortcmd = ["sort by %s;" % sort]
    else:
        sortcmd = []

    # Build the CQP query
    cmd = []

    if use_cache:
        cmd += ['set DataDirectory "%s";' % cache_dir]

    cmd += ["%s;" % corpus]

    # This prints the attributes and their relative order:
    cmd += cwb.show_attributes()

    retcode = 0

    if is_cached:
        # This exact query has been done before. Read corpus positions from cache.
        if not cached_no_hits:
            cmd += ["Last = %s;" % cache_query]
            # Touch cache file to delay its removal
            os.utime(cache_filename)
    else:
        for i, c in enumerate(cqp):
            cqpparams_temp = cqpparams.copy()
            pre_query = i + 1 < len(cqp)

            if pre_query and expand_prequeries:
                cqpparams_temp["expand"] = "to " + within

            if free_search:
                retcode, free_query = utils.query_optimize(c, cqpparams_temp, free_search=True)
                if retcode == 2:
                    raise utils.CQPError("Couldn't convert into free order query.")
                cmd += free_query
            elif do_optimize and expand_prequeries:
                # If expand_prequeries is False, we can't use optimization
                cmd += utils.query_optimize(c, cqpparams_temp, find_match=(not pre_query))[1]
            else:
                cmd += utils.make_query(utils.make_cqp(c, **cqpparams_temp))

            if pre_query:
                cmd += ["Last;"]

    if use_cache and cached_no_hits:
        # Print EOL if no hits
        cmd += [".EOL.;"]
    else:
        # This prints the size of the query (i.e., the number of results):
        cmd += ["size Last;"]

    if use_cache and not is_cached:
        cmd += ["%s = Last; save %s;" % (cache_query_temp, cache_query_temp)]

    if not no_results and not (use_cache and cached_no_hits):
        if free_search and retcode == 0:
            tokens, _ = utils.parse_cqp(cqp[-1])
            cmd += ["Last;"]
            cmd += ["cut %s %s;" % (start, end)]
            cmd += utils.make_query(utils.make_cqp("(%s)" % " | ".join(set(tokens)), **cqpparams))

        cmd += ["show +%s;" % " +".join(show)]
        if len(context) == 1:
            cmd += ["set Context %s;" % context[0]]
        else:
            cmd += ["set LeftContext %s;" % context[0]]
            cmd += ["set RightContext %s;" % context[1]]
        cmd += ["set LeftKWICDelim '%s '; set RightKWICDelim ' %s';" % (utils.LEFT_DELIM, utils.RIGHT_DELIM)]
        if show_structs:
            cmd += ["set PrintStructures '%s';" % ", ".join(show_structs)]
        cmd += ["set ExternalSort yes;"]
        cmd += sortcmd
        if free_search:
            cmd += ["cat Last;"]
        else:
            cmd += ["cat Last %s %s;" % (start, end)]

    cmd += ["exit;"]

    ######################################################################
    # Then we call the CQP binary, and read the results
    lines = cwb.run_cqp(cmd, attr_ignore=True, abort_event=abort_event)

    # Skip the CQP version
    next(lines)

    # Remove cache file if it exceeds max cache file size
    if use_cache and not is_cached and cache_max_query_data:
        cache_file = os.path.join(cache_dir, f"{corpus}:{cache_query_temp}")
        try:
            if os.path.isfile(cache_file) and os.path.getsize(cache_file) > cache_max_query_data:
                os.remove(cache_file)
        except FileNotFoundError:
            pass

    # Read the attributes and their relative order
    attrs = cwb.read_attributes(lines)

    # Read the size of the query, i.e., the number of results
    nr_hits = next(lines)
    nr_hits = 0 if nr_hits == utils.END_OF_LINE else int(nr_hits)

    if use_cache and not is_cached and not cached_no_hits:
        # Save number of hits
        with memcached.get_client() as mc:
            mc.add(cache_size_key, nr_hits)

        try:
            os.rename(cache_filename_temp, cache_filename)
        except FileNotFoundError:
            pass
    return lines, nr_hits, attrs

def write_dict_to_json(data_dict, file_path):
    """Write a dictionary to a JSON file.

    Args:
        data_dict (dict): The dictionary to write.
        file_path (str): The path to the file where the JSON will be saved.
    """
    with open(file_path, 'w') as json_file:
        json.dump(data_dict, json_file, indent=4)


def query_parse_lines(corpus, lines, attrs, show, show_structs, free_matches=False, abort_event=None):
    """Parse concordance lines from CWB."""

    # Filter out unavailable attributes
    p_attrs = [attr for attr in attrs["p"] if attr in show]
    nr_splits = len(p_attrs)
    s_attrs = set(attr for attr in attrs["s"] if attr in show)
    ls_attrs = set(attr for attr in attrs["s"] if attr in show_structs)
    # a_attrs = set(attr for attr in attrs["a"] if attr in shown)

    last_line_span = ()
    
    kwic = []
    matchestemp = []
    for line in lines:
        if abort_event and abort_event.is_set():
            return
        linestructs = {}
        match = {}

        header, line = line.split(":", 1)
        if header[:3] == "-->":
            # For aligned corpora, every other line is the aligned result
            aligned = header[3:]
        else:
            # This is the result row for the query corpus
            aligned = None
            match["position"] = int(header)

        # Handle PrintStructures
        if ls_attrs and not aligned: #skipib esimesel otsingul
            if ":  " in line:
                lineattr, line = line.rsplit(":  ", 1)
            else:
                # Sometimes, depending on context, CWB uses only one space instead of two as a separator
                lineattr, line = line.split(">: ", 1)
                lineattr += ">"

            lineattrs = lineattr[2:-1].split("><")

            # Handle "><" in attribute values
            if not len(lineattrs) == len(ls_attrs):
                new_lineattrs = []
                for la in lineattrs:
                    if not la.split(" ", 1)[0] in ls_attrs:
                        new_lineattrs[-1] += "><" + la
                    else:
                        new_lineattrs.append(la)
                lineattrs = new_lineattrs

            for s in lineattrs:
                if s in ls_attrs:
                    s_key = s
                    s_val = None
                else:
                    s_key, s_val = s.split(" ", 1)

                linestructs[s_key] = s_val

        words = utils.split_response(line, nr_splits)
        currentPhrase = []
        lastPhrase = []
        phraseStack = [currentPhrase]
        n = [0]
        N = 0
        i = 0

        try:
            for j, word in enumerate(words):
                # Check if the word is a special string (delimiter or tag)
                if isinstance(word, str):
                    if word == utils.LEFT_DELIM:
                        if "phrase" in words[j+1]: # For when the matched word is the first word in a phrase
                            n.append(0)
                        match["start"] = n.copy()
                        match["start_id"] = str(N + 1)
                    elif word == utils.RIGHT_DELIM:
                        if len(match["start"]) != len(n): # To compensate for when the matched word is the first word in a phrase
                            n.pop()
                        match["end"] = n.copy()
                    elif "/phrase" in word:  # End of phrase block
                        if "end" not in match:
                            i -= 1
                            n[i] += 1
                            n.pop()
                        
                        errors = {'error_correction': {}, 'error_type': {}}
                        phraseWordCount = 0
                        # Count how the frequency of an attribute among the tokens
                        for phraseWord in currentPhrase:
                            if "phrase_tokens" in phraseWord: continue
                            phraseWordCount += 1
                            for x in ["error_correction", "error_type"]:
                                errorTypes = phraseWord[x].split("|")
                                errorTypes = [re.sub(r'\[\d+\]$', '', s) for s in errorTypes]
                                for cor in errorTypes:
                                    if cor in errors[x]: errors[x][cor] += 1
                                    else: errors[x][cor] = 1
                        
                        for x in ["error_correction", "error_type"]:
                            phraseErrs = set()
                            errs = set()
                            for phraseWord in currentPhrase:
                                if "phrase_tokens" in phraseWord: continue
                                corrections = phraseWord[x].split("|")
                                for cor in corrections:
                                    cor = re.sub(r'\[\d+\]$', '', cor)
                                    if errors[x][cor] == phraseWordCount:
                                        phraseErrs.add(cor)
                                    else:
                                        errs.add(cor)
                                if len(errs) == 0: phraseWord[x] = "_"
                                else: phraseWord[x] = "|".join(errs)
                            errors[x] = list(phraseErrs)
                            if x == "error_correction":
                                errors[x] = list(phraseErrs)[-1]

                        lastPhrase = phraseStack.pop()
                        lastPhrase.append({'phrase_tokens': currentPhrase, 'error': errors})
                        currentPhrase = lastPhrase
                    elif "phrase" in word:  # Start of phrase block
                        if "end" not in match:
                            n.append(0)
                            i += 1
                        phraseStack.append(currentPhrase)
                        currentPhrase = []
                    continue
                currentPhrase.append(process_token(word, p_attrs))

                n[i] += 1
                N += 1

            kwic.append({"corpus": corpus, "match": match, "structs": {}, "tokens": currentPhrase})

        except RuntimeError as e:
            print(e)
            # Skip lines with unparseable attributes due to special characters
            continue

    return kwic

def process_token(word_data, attribute_list):
    """
    Process a token that is not within a phrase_with_errors.
    Assigns attributes based on attribute_list.
    """
    return {attribute: word_data[index] for index, attribute in enumerate(attribute_list)}

def query_and_parse(corpus, cqp, within=None, cut=None, context=None, show=None, show_structs=None, start=0, end=10,
                    sort=None, random_seed=None, no_results=False, expand_prequeries=True, free_search=False,
                    use_cache=False, cache_dir=None, cache_max_query_data=0, abort_event=None):
    lines, nr_hits, attrs = query_corpus(corpus, cqp, within, cut, context, show, show_structs, start, end, sort,
                                         random_seed, no_results, expand_prequeries, free_search, use_cache, cache_dir,
                                         cache_max_query_data, abort_event)
    kwic = query_parse_lines(corpus, lines, attrs, show, show_structs, free_matches=free_search,
                             abort_event=abort_event)
    return kwic, nr_hits


def which_hits(corpora, stats, start, end):
    corpus_hits = {}
    for corpus in corpora:
        hits = stats[corpus]
        if hits > start:
            corpus_hits[corpus] = (start, min(hits - 1, end))

        start -= hits
        end -= hits
        if start < 0:
            start = 0
        if end < 0:
            break

    return corpus_hits
