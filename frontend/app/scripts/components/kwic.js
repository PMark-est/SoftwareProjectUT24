/** @format */
import angular from "angular"
import _ from "lodash"
import statemachine from "@/statemachine"
import settings from "@/settings"
import currentMode from "@/mode"
import { makeDownload } from "@/kwic_download"
import { SelectionManager, html, setDownloadLinks } from "@/util"
import "@/components/kwic-pager"
import "@/components/kwic-word"
import "@/components/filter"
import "@/components/wordColorMeanings"
import "@/services/popups"
import { generateColors } from "@/colors"

angular.module("korpApp").component("kwic", {
    template: html`
        <div ng-if="$ctrl.aborted && !$ctrl.loading" class="korp-warning">{{'search_aborted' | loc:$root.lang}}</div>

        <div ng-if="!$ctrl.aborted || $ctrl.loading" ng-click="$ctrl.onKwicClick($event)">
            <div class="result_controls">
                <div class="controls_n" ng-if="$ctrl.hitsInProgress != null">
                    <span>{{'num_results' | loc:$root.lang}}: </span>
                    <span class="num-result">{{ $ctrl.hitsInProgress | prettyNumber:$root.lang }}</span>
                </div>
                <div class="hits_picture" ng-if="$ctrl.hitsPictureData.length > 1">
                    <table class="hits_picture_table">
                        <tbody>
                            <tr>
                                <td
                                    class="hits_picture_corp"
                                    ng-repeat="corpus in $ctrl.hitsPictureData"
                                    ng-style='{width : corpus.relative + "%"}'
                                    ng-class="{odd : $index % 2 != 0, even : $index % 2 == 0}"
                                    ng-click="$ctrl.pageEvent(corpus.page)"
                                    uib-tooltip="{{corpus.rtitle | locObj:$root.lang}}: {{corpus.abs}}"
                                    tooltip-placement='{{$last? "left":"top"}}'
                                    append-to-body="false"
                                ></td>
                            </tr>
                        </tbody>
                    </table>
                </div>
            </div>
            <kwic-pager
                ng-if="$ctrl.hits"
                total-hits="$ctrl.hits"
                current-page="$ctrl.page"
                page-change="$ctrl.pageEvent(page)"
                hits-per-page="$ctrl.hitsPerPage"
            ></kwic-pager>
            <filter
                search="$ctrl.performedSearch"
                on-kwic-change="$ctrl.handleKwicChange(newKwic)"
                kwic-hits="$ctrl.kwic"
            ></filter>
            <span ng-if="$ctrl.hits" class="reading_btn link" ng-click="$ctrl.toggleReading()">
                <span ng-if="!$ctrl.isReading">{{'show_reading' | loc:$root.lang}}</span>
                <span ng-if="$ctrl.isReading">{{'show_kwic' | loc:$root.lang}}</span>
            </span>
            <span ng-if="$ctrl.hits">
                <word-color-meanings
                    change-color="$ctrl.updateColor(error)"
                ></word-color-meanings>
            </span>
            <div class="table_scrollarea">
                <table class="results_table kwic" ng-if="!$ctrl.useContext" cellspacing="0">
                    <tr
                        class="sentence"
                        ng-repeat="sentence in $ctrl.kwic"
                        ng-class="{corpus_info : sentence.newCorpus, linked_sentence : sentence.isLinked, even : $even, odd : $odd}"
                    >
                        <td ng-if="::sentence.newCorpus" />
                        <td ng-if="::sentence.newCorpus" colspan="2" class="text-gray-600 uppercase">
                            <div class="w-0">
                                {{sentence.newCorpus | locObj:$root.lang}}
                                <span class="normal-case" ng-if="::sentence.noContext">
                                    ({{'no_context_support' | loc:$root.lang}})
                                </span>
                            </div>
                        </td>

                        <td ng-if="::sentence.isLinked" colspan="3" class="lnk">
                            <kwic-word
                                ng-repeat="word in sentence.tokens"
                                word="word"
                                sentence="sentence"
                                sentence-index="$parent.$index"
                            />
                        </td>

                        <td ng-if="::!sentence.newCorpus && !sentence.isLinked" class="left">
                            <kwic-word
                                ng-repeat="word in $ctrl.selectLeft(sentence)"
                                word="word"
                                sentence="sentence"
                                sentence-index="$parent.$index"
                            />
                        </td>
                        <td ng-if="::!sentence.newCorpus && !sentence.isLinked" class="center">
                            <kwic-word
                                ng-repeat="word in $ctrl.selectMatch(sentence)"
                                word="word"
                                sentence="sentence"
                                sentence-index="$parent.$index"
                            />
                        </td>
                        <td ng-if="::!sentence.newCorpus && !sentence.isLinked" class="right">
                            <kwic-word
                                ng-repeat="word in $ctrl.selectRight(sentence)"
                                word="word"
                                sentence="sentence"
                                sentence-index="$parent.$index"
                            />
                        </td>
                    </tr>
                </table>

                <div class="results_table reading" ng-if="$ctrl.useContext">
                    <p
                        class="sentence"
                        ng-repeat="sentence in $ctrl.kwic"
                        ng-class="{corpus_info : sentence.newCorpus, linked_sentence : sentence.isLinked, even : $even, odd : $odd}"
                    >
                        <span ng-if="sentence.newCorpus" class="corpus_title text-3xl">
                            {{sentence.newCorpus | locObj:$root.lang}}
                            <span class="corpus_title_warn block text-base" ng-if="::sentence.noContext">
                                ({{'no_context_support' | loc:$root.lang}})
                            </span>
                        </span>
                        <kwic-word
                            ng-if="!sentence.newCorpus"
                            ng-repeat="word in sentence.tokens"
                            word="word"
                            sentence="sentence"
                            sentence-index="$parent.$index"
                        />
                    </p>
                </div>
            </div>
            <kwic-pager
                ng-if="$ctrl.hits"
                total-hits="$ctrl.hits"
                current-page="$ctrl.page"
                page-change="$ctrl.pageEvent(page)"
                hits-per-page="$ctrl.hitsPerPage"
            ></kwic-pager>
            <div ng-if="!$ctrl.loading">
                <select id="download-links" ng-if="$ctrl._settings['enable_backend_kwic_download']"></select>
                <select
                    id="frontendDownloadLinks"
                    ng-if="$ctrl._settings['enable_frontend_kwic_download']"
                    ng-change="$ctrl.download.init($ctrl.download.selected, $ctrl.hits)"
                    ng-model="$ctrl.download.selected"
                    ng-options="item.value as item.label | loc:$root.lang disable when item.disabled for item in $ctrl.download.options"
                ></select>
                <a
                    class="kwicDownloadLink"
                    ng-if="$ctrl._settings['enable_frontend_kwic_download']"
                    href="{{$ctrl.download.blobName}}"
                    download="{{$ctrl.download.fileName}}"
                    target="_self"
                    style="display: none;"
                ></a>
            </div>
        </div>
    `,
    bindings: {
        aborted: "<",
        loading: "<",
        active: "<",
        hitsInProgress: "<",
        hits: "<",
        isReading: "<",
        page: "<",
        pageEvent: "<",
        contextChangeEvent: "<",
        hitsPerPage: "<",
        prevParams: "<",
        prevRequest: "<",
        corpusOrder: "<",
        /** Current page of results. */
        kwicInput: "<",
        corpusHits: "<",
    },
    controller: [
        "$location",
        "$element",
        "$timeout",
        "$scope",
        "popupService",
        "$http",
        /**
         * @param {import("angular").ILocationService} $location
         * @param {JQLite} $element
         * @param {import("angular").ITimeoutService} $timeout
         */
        function ($location, $element, $timeout, $scope, popupService, $http) {
            let $ctrl = this

            const selectionManager = new SelectionManager()

            $ctrl.getClass = (sentence) => {
                if (!sentence.match) return
                let classes = []
                if (sentence.match.phrase) {
                    classes.push({
                        has_error: sentence.tokens[sentence.match.phrase].error.error_tag,
                    })
                    classes.push(sentence.tokens[sentence.match.phrase].error.error_type)
                } else {
                }
                return classes
            }

            $ctrl.$onInit = () => {
                addKeydownHandler()
            }

            $ctrl.handleKwicChange = function (newKwic) {
                $ctrl.kwic = newKwic
                addColors()
            }

            $ctrl.$onChanges = (changeObj) => {
                $ctrl.performedSearch = false
                if ("kwicInput" in changeObj && $ctrl.kwicInput != undefined) {
                    $ctrl.kwic = massageData($ctrl.kwicInput)
                    $ctrl.useContext = $ctrl.isReading || $location.search()["in_order"] != null
                    if (!$ctrl.isReading) {
                        $timeout(() => {
                            centerScrollbar()
                            $element.find(".match").children().first().click()
                        })
                    }

                    if (settings["enable_backend_kwic_download"]) {
                        setDownloadLinks($ctrl.prevRequest, {
                            kwic: $ctrl.kwic,
                            corpus_order: $ctrl.corpusOrder,
                        })
                    }

                    if (currentMode === "parallel" && !$ctrl.isReading) {
                        $timeout(() => alignParallelSentences())
                    }
                    if ($ctrl.kwic.length == 0) {
                        selectionManager.deselect()
                        statemachine.send("DESELECT_WORD")
                    }
                    $timeout(() => {
                        $ctrl.performedSearch = true
                    }, 500)
                }
                if ("corpusHits" in changeObj && $ctrl.corpusHits) {
                    let items = _.map($ctrl.corpusOrder, (obj) => ({
                        rid: obj,
                        rtitle: settings.corpusListing.getTitleObj(obj.toLowerCase()),
                        relative: $ctrl.corpusHits[obj] / $ctrl.hits,
                        abs: $ctrl.corpusHits[obj],
                    })).filter((item) => item.abs > 0)

                    // calculate which is the first page of hits for each item
                    let index = 0
                    _.each(items, (obj) => {
                        // $ctrl.kwicInput.length == page size
                        obj.page = Math.floor(index / $ctrl.kwicInput.length)
                        index += obj.abs
                    })

                    $ctrl.hitsPictureData = items
                }

                if ("active" in changeObj) {
                    if ($ctrl.active) {
                        $timeout(() => $element.find(".token_selected").click(), 0)
                    } else {
                        statemachine.send("DESELECT_WORD")
                    }
                }

                addColors()
            }

            $ctrl.onKwicClick = (event) => {
                if (event.target.classList.contains("word")) {
                    onWordClick(event)
                } else {
                    popupService.showPopups(-1)
                    if (
                        event.target.id === "frontendDownloadLinks" ||
                        event.target.classList.contains("kwicDownloadLink") ||
                        event.target.classList.contains("hits_picture_corp")
                    ) {
                        return
                    }
                    if (!selectionManager.hasSelected()) {
                        return
                    }
                    selectionManager.deselect()
                    statemachine.send("DESELECT_WORD")
                }
            }

            $ctrl._settings = settings

            $ctrl.toggleReading = () => {
                // Emit event; parent should update isReading
                $ctrl.contextChangeEvent()
            }

            $ctrl.download = {
                options: [
                    { value: "", label: "download_kwic" },
                    { value: "kwic/csv", label: "download_kwic_csv" },
                    { value: "kwic/tsv", label: "download_kwic_tsv" },
                    { value: "annotations/csv", label: "download_annotations_csv", disabled: settings["parallel"] },
                    { value: "annotations/tsv", label: "download_annotations_tsv", disabled: settings["parallel"] },
                ],
                selected: "",
                init: (value, hits) => {
                    if ($ctrl.download.blobName) {
                        URL.revokeObjectURL($ctrl.download.blobName)
                    }
                    if (value === "") {
                        return
                    }
                    const [fileName, blobName] = makeDownload(...value.split("/"), $ctrl.kwic, $ctrl.prevParams, hits)
                    $ctrl.download.fileName = fileName
                    $ctrl.download.blobName = blobName
                    $ctrl.download.selected = ""
                    $timeout(() => $element[0].getElementsByClassName("kwicDownloadLink")[0].click(), 0)
                },
            }

            $ctrl.selectLeft = function (sentence) {
                if (!sentence.match) {
                    return
                }
                return sentence.tokens.slice(0, sentence.match.start[0])
            }

            $ctrl.selectMatch = function (sentence) {
                if (!sentence.match) {
                    return
                }
                const from = sentence.match.start[0]
                let end = sentence.match.end[0]
                if (sentence.match.start.length != 1) {
                    end += 1
                }
                return sentence.tokens.slice(from, end)
            }

            $ctrl.selectRight = function (sentence) {
                if (!sentence.match) {
                    return
                }
                const len = sentence.tokens.length
                let from = sentence.match.end[0]
                if (sentence.match.start.length != 1) {
                    from += 1
                }
                return sentence.tokens.slice(from, len)
            }

            $ctrl.currentErrorColor = "_"

            $ctrl.updateColor = function(error = "_") {
                $ctrl.currentErrorColor = error
                addColors()
            }

            function addColors() {
                $timeout(() => {
                    if (!$ctrl.kwic) return

                    const errorTypes = new Set()
                    const apiUrl = `${settings.korp_backend_url}/lexicon?positional_attribute=error_type`

                    $http.get(apiUrl).then((response) => {
                        const resp = response.data.Arguments
                        for (let index = 0; index < resp.length; index++) {
                            const error_type = resp[index]
                            if (error_type === "_" || error_type === "__UNDEF__" || error_type === "") continue
                            const parts = error_type.split("|")
                            for (let index = 0; index < parts.length; index++) {
                                const part = parts[index]
                                errorTypes.add(part)
                            }
                        }

                        // Generate color gradient based on error types
                        const colors = [
                            ...generateColors("#FA9189", "#D1BDFF", Math.floor(errorTypes.size / 2)),
                            ...generateColors("#7AD6EB", "#46E079", errorTypes.size - Math.floor(errorTypes.size / 2)),
                        ]

                        //Delete old colors
                        ;[...errorTypes].forEach((error, index) => {
                            ;[...document.getElementsByClassName(error)].forEach((word) => {
                                word.removeAttribute("style")
                            })
                        })

                        // Apply color styles to each error type
                        ;[...errorTypes].forEach((error, index) => {
                            //console.log(error)
                            if (error == $ctrl.currentErrorColor || $ctrl.currentErrorColor == "_") {
                                ;[...document.getElementsByClassName(error)].forEach((word) => {
                                    let tag = `background-color:${colors[index]};`
                                    //Add error tag to all words in a phrase, so we can add gradients to them correctly
                                    if (word.classList.contains("phrase")) {
                                        [...word.getElementsByClassName("word")].forEach((phraseWord) => {
                                            if (!phraseWord.className.contains(error)) {
                                                phraseWord.className += " " + error
                                            }
                                            if (!phraseWord.className.contains("has_error")) {
                                                phraseWord.className += " has_error"
                                            }
                                        })
                                    }
                                    //Add a color to error words without a color   
                                    if (word.getAttribute("style") == null) {
                                        word.setAttribute("style", tag)
                                    } else {
                                        //Create a gradient if a word already has a color
                                        let styles = word.getAttribute("style").split(";")
                                        let prevColor = styles[0].split(":")[1]
                                        let gradients = new Set()
                                        gradients.add(prevColor)
                                        if (styles[1] != "") {
                                            //For whatever reason regex doesn't get all the colors...
                                            /*
                                            for (let color of styles[1].match(/#[\d|\w]+/)) {
                                                gradients.add(color)
                                            }
                                            */
                                            for (let color of styles[1].split("(")[1].split(",").slice(1)) {
                                                gradients.add(color.match(/#[\d|\w]+/)[0])
                                            }
                                        }
                                        gradients.add(colors[index])
                                        gradients = Array.from(gradients)
                                        tag = `background-color:${prevColor}; background-image: linear-gradient(to top, ${gradients});`
                                        word.setAttribute("style", tag)
                                    }
                                })
                            }
                        })
                    })
                }, 50)
            }

            function massageData(hitArray) {
                const punctArray = [",", ".", ";", ":", "!", "?", "..."]
                let prevCorpus = "" // Tracks the previous corpus to handle corpus changes
                const output = [] // Stores the transformed data for output

                // Process each item in hitArray (each item represents a 'hit' with context data)
                hitArray.forEach((hitContext) => {
                    // Get the corpus ID and main corpus ID, based on the mode (parallel or single corpus)
                    const { corpusId, mainCorpusId } = getCorpusIds(hitContext)

                    // Determine the match start and end positions
                    const matches = getMatchRanges(hitContext)

                    // Initialize object for tracking open structs during token processing
                    const currentStruct = {}

                    // Process each token (either a word or a phrase) in the hit context
                    hitContext.tokens.forEach((token, index) => {
                        token.position = index // Set position for each token
                        processToken(token, matches, punctArray, currentStruct, corpusId)
                    })

                    // Handle new corpus headers if corpus changes
                    if (prevCorpus !== corpusId) {
                        const corpus = settings.corpora[corpusId]
                        output.push(createCorpusHeader(corpus))
                    }

                    hitContext.corpus = mainCorpusId // Set main corpus ID for consistency in output
                    output.push(hitContext) // Add processed hit context to output

                    // Process aligned tokens if they exist, especially for parallel mode
                    if (hitContext.aligned) {
                        const [alignedCorpus, alignedTokens] = Object.entries(hitContext.aligned)[0]
                        markOpenSentencesInAligned(alignedTokens) // Mark open sentences in aligned tokens
                        output.push({
                            tokens: alignedTokens,
                            isLinked: true,
                            corpus: alignedCorpus,
                        })
                    }

                    prevCorpus = corpusId // Update prevCorpus to current corpus ID for next iteration
                })

                return output // Return the final transformed output array
            }

            // Helper function to determine corpus IDs, handling parallel mode if necessary
            function getCorpusIds(hitContext) {
                let mainCorpusId, linkCorpusId
                if (currentMode === "parallel") {
                    ;[mainCorpusId, linkCorpusId] = hitContext.corpus.toLowerCase().split("|")
                } else {
                    mainCorpusId = hitContext.corpus.toLowerCase()
                }
                return { corpusId: linkCorpusId || mainCorpusId, mainCorpusId }
            }

            // Helper function to get match ranges from hitContext, supporting multiple matches
            function getMatchRanges(hitContext) {
                if (Array.isArray(hitContext.match)) {
                    return hitContext.match.map(({ start, end }) => ({ start, end }))
                } else {
                    return [{ start: hitContext.match.start, end: hitContext.match.end }]
                }
            }

            // Process each token in hitContext, marking matches, punctuation, and structures
            function processToken(token, matches, punctArray, currentStruct, corpusId) {
                // Mark token if it's within any match range
                matches.forEach(({ start, end }) => {
                    if (start <= token.position && token.position < end) {
                        token._match = true
                    }
                })

                // Mark if token is punctuation
                if (punctArray.includes(token.word)) {
                    token._punct = true
                }

                // Initialize structs if not already
                token.structs = token.structs || {}

                // Handle struct 'open' and 'close' attributes
                handleStructs(token, currentStruct, corpusId)

                // Apply accumulated attributes from current struct to token
                const structAttributes = Object.values(currentStruct).reduce(
                    (acc, struct) => Object.assign(acc, struct),
                    {}
                )
                Object.assign(token, structAttributes)
            }

            // Handles struct 'open' and 'close' for tokens, updating currentStruct
            function handleStructs(token, currentStruct, corpusId) {
                token.structs.open?.forEach((structItem) => {
                    const structKey = Object.keys(structItem)[0]
                    currentStruct[structKey] = createStructAttributes(structItem, structKey, corpusId)
                    if (structKey === "sentence") {
                        token._open_sentence = true
                    }
                })

                // Close structs as necessary
                token.structs.close?.forEach((structKey) => {
                    delete currentStruct[structKey]
                })
            }

            // Helper function to create structured attributes for a struct item based on corpus settings
            function createStructAttributes(structItem, structKey, corpusId) {
                const attrs = Object.entries(structItem[structKey]).map(([key, value]) => [
                    `${structKey}_${key}`,
                    value,
                ])
                const corpusAttributes = settings.corpora[corpusId].attributes
                return Object.fromEntries(attrs.filter(([key]) => key in corpusAttributes))
            }

            // Helper function to create a new corpus header for output
            function createCorpusHeader(corpus) {
                return {
                    newCorpus: corpus.title,
                    noContext: Object.keys(corpus.context).length === 1,
                }
            }

            // Marks sentences as open in aligned tokens
            function markOpenSentencesInAligned(alignedTokens) {
                alignedTokens.forEach((token) => {
                    if (token.structs?.open) {
                        token.structs.open.forEach((structItem) => {
                            if (Object.keys(structItem)[0] === "sentence") {
                                token._open_sentence = true
                            }
                        })
                    }
                })
            }

            function onWordClick(event) {
                event.stopPropagation()
                const scope = $(event.target).scope()
                let obj
                if (scope.word.word) obj = scope.word
                else obj = scope.word.phrase_tokens
                const sent = scope.sentence
                const word = $(event.target)

                if ($ctrl.active) {
                    if (scope.word.word)
                        statemachine.send("SELECT_WORD", {
                            sentenceData: sent.structs,
                            wordData: obj,
                            corpus: sent.corpus.toLowerCase(),
                            tokens: sent.tokens,
                            inReadingMode: false,
                        })
                    else {
                        const clicked_word = word[0].innerText
                        let token
                        for (let index = 0; index < scope.word.phrase_tokens.length; index++) {
                            const element = scope.word.phrase_tokens[index]
                            if (element.word === clicked_word) token = element
                        }
                        statemachine.send("SELECT_WORD", {
                            sentenceData: sent.structs,
                            wordData: token,
                            corpus: sent.corpus.toLowerCase(),
                            tokens: sent.tokens,
                            inReadingMode: false,
                        })
                    }
                }

                if (currentMode === "parallel") {
                    selectWordParallel(word, scope, sent)
                } else {
                    selectWord(word, scope)
                }

                popupService.showPopups(scope.sentenceIndex)
            }

            function selectWord(word, scope) {
                const obj = scope.word
                let aux = null
                if (obj.dephead != null) {
                    const i = Number(obj.dephead)

                    const paragraph = word.closest(".sentence").find(".word")
                    let sent_start = 0
                    const querySentStart = ".open_sentence"
                    if (word.is(querySentStart)) {
                        sent_start = paragraph.index(word)
                    } else {
                        const l = paragraph.filter((__, item) => $(item).is(word) || $(item).is(querySentStart))
                        sent_start = paragraph.index(l.eq(l.index(word) - 1))
                    }
                    aux = $(paragraph.get(sent_start + i - 1))
                }
                selectionManager.select(word, aux)
            }

            /** Select a given token, follow links to different languages and give linked tokens a secondary highlighting. */
            function selectWordParallel(word, scope, sentence) {
                // Select the given word.
                selectWord(word, scope)

                // Clear any previous linked-token highlighting.
                clearLinks()

                var obj = scope.word
                if (!obj.linkref) return
                var corpus = settings.corpora[sentence.corpus]
                var [mainCorpus, lang] = corpus.id.split("-")

                function findRef(ref, sentence) {
                    var out = null
                    _.each(sentence, function (word) {
                        if (word.linkref == ref.toString()) {
                            out = word
                            return false
                        }
                    })
                    return out
                }

                if (sentence.isLinked) {
                    // a secondary language was clicked
                    var sent_index = scope.sentenceIndex
                    var data = getActiveData()

                    // Find main sentence, as nearest previous non-linked sentence.
                    var mainSent = null
                    while (data[sent_index]) {
                        var sent = data[sent_index]
                        if (!sent.isLinked) {
                            mainSent = sent
                            break
                        }
                        sent_index--
                    }

                    var linkNum = Number(obj.linkref)

                    // Find linked tokens in main sentence and highlight them.
                    _.each(mainSent.tokens, function (token) {
                        var refs = _.map(_.compact(token["wordlink-" + lang].split("|")), Number)
                        if (_.includes(refs, linkNum)) {
                            token._link_selected = true
                            $ctrl.parallelSelected.push(token)
                        }
                    })
                } else {
                    // Collect references to linked tokens from wordlink-(lang) values
                    var links = _.pickBy(obj, function (val, key) {
                        return _.startsWith(key, "wordlink")
                    })
                    // Follow each link and highlight linked tokens
                    _.each(links, function (val, key) {
                        var lang = key.split("-")[1]
                        _.each(_.compact(val.split("|")), function (num) {
                            const link = findRef(num, sentence.aligned[mainCorpus + "-" + lang])
                            if (!link) return
                            link._link_selected = true
                            $ctrl.parallelSelected.push(link)
                        })
                    })
                }
            }

            function getActiveData() {
                return $ctrl.kwic
            }

            function clearLinks() {
                _.each($ctrl.parallelSelected, function (word) {
                    delete word._link_selected
                })
                $ctrl.parallelSelected = []
            }

            function centerScrollbar() {
                const m = $element.find(".match:first")
                if (!m.length) {
                    return
                }
                const area = $element.find(".table_scrollarea").scrollLeft(0)
                const match = m.first().position().left + m.width() / 2
                const sidebarWidth = $("#sidebar").outerWidth() || 0
                area.stop(true, true).scrollLeft(match - ($("body").innerWidth() - sidebarWidth) / 2)
            }

            /** Add offsets to align each linked sentence with its main one */
            function alignParallelSentences() {
                /** A helper to get horizontal coordinates relative to a container. */
                function getBounds($elements, $container) {
                    const container = $container.get(0).getBoundingClientRect()
                    const left = $elements.get(0).getBoundingClientRect().left - container.left
                    const right = $elements.get(-1).getBoundingClientRect().right - container.left
                    const width = right - left
                    const center = left + width / 2
                    const space = container.width - width
                    return { left, right, width, center, space }
                }

                $(".table_scrollarea > .kwic .linked_sentence").each((i, el) => {
                    const $linkedRow = $(el)
                    const $mainRow = $linkedRow.prev()
                    const linked = getBounds($linkedRow.find(".word"), $linkedRow)
                    const main = getBounds($mainRow.find(".word"), $mainRow)

                    const offset = main.center - linked.width / 2
                    // Add offset as cell padding
                    $linkedRow.find(".lnk").css("padding-left", Math.min(offset, linked.space))
                })
            }

            function addKeydownHandler() {
                $(document).keydown((event) => {
                    let next
                    const isSpecialKeyDown = event.shiftKey || event.ctrlKey || event.metaKey
                    if (isSpecialKeyDown || $("input, textarea, select").is(":focus")) {
                        // TODO || !$element.is(":visible")) {
                        return
                    }

                    switch (event.which) {
                        case 78: // n
                            $ctrl.pageEvent($ctrl.page + 1)
                            return false
                        case 70: // f
                            if ($ctrl.page === 0) {
                                return
                            }
                            $ctrl.pageEvent($ctrl.page - 1)
                            return false
                    }
                    if (!selectionManager.hasSelected()) {
                        return
                    }
                    switch (event.which) {
                        case 38: // up
                            next = selectUp()
                            break
                        case 39: // right
                            next = selectNext()
                            break
                        case 37: // left
                            next = selectPrev()
                            break
                        case 40: // down
                            next = selectDown()
                            break
                    }

                    if (next) {
                        next.trigger("click")
                        scrollToShowWord(next)
                        return false
                    }
                })
            }

            function selectNext() {
                return stepWord(1)
            }

            function selectPrev() {
                return stepWord(-1)
            }

            function stepWord(diff) {
                const $words = $element.find(".word")
                const $current = $element.find(".token_selected").first()
                const currentIndex = $words.index($current)
                const wouldWrap = (diff < 0 && currentIndex == 0) || (diff > 0 && currentIndex == $words.length - 1)
                if (wouldWrap) return
                const next = $words.get(currentIndex + diff)
                return $(next)
            }

            function selectUp() {
                const current = selectionManager.selected
                const $prevSentence = current.closest(".sentence").prev(":not(.corpus_info)")

                if (!$ctrl.isReading) {
                    return getWordAt(current.offset().left + current.width() / 2, $prevSentence)
                }

                const searchwords = current.prevAll(".word").get().concat($prevSentence.find(".word").get().reverse())
                const def = $prevSentence.find(".word:last")
                return getFirstAtCoor(current.offset().left + current.width() / 2, $(searchwords), def)
            }

            function selectDown() {
                const current = selectionManager.selected
                const $nextSentence = current.closest(".sentence").next(":not(.corpus_info)")

                if (!$ctrl.isReading) {
                    return getWordAt(current.offset().left + current.width() / 2, $nextSentence)
                }

                const searchwords = current.nextAll(".word").add($nextSentence.find(".word"))
                const def = $nextSentence.find(".word:last")
                return getFirstAtCoor(current.offset().left + current.width() / 2, searchwords, def)
            }

            /**
             * @param {number} x
             * @param {JQLite} wds
             * @param {JQLite} default_word
             */
            function getFirstAtCoor(x, wds, default_word) {
                const isHit = (word) => x > $(word).offset().left && x < $(word).offset().left + $(word).width()
                const hit = wds.get().find(isHit)
                return hit ? $(hit) : default_word
            }

            function getWordAt(xCoor, $row) {
                let output = $()
                $row.find(".word").each(function () {
                    output = $(this)
                    const thisLeft = $(this).offset().left
                    const thisRight = $(this).offset().left + $(this).width()
                    if ((xCoor > thisLeft && xCoor < thisRight) || thisLeft > xCoor) {
                        return false
                    }
                })

                return output
            }

            /**
             * @param {JQLite} word
             */
            function scrollToShowWord(word) {
                if (!word.length) return
                const offset = 200

                if (word.offset().top + word.height() > window.scrollY + $(window).height()) {
                    $("html, body")
                        .stop(true, true)
                        .animate({ scrollTop: window.scrollY + offset })
                } else if (word.offset().top < window.scrollY) {
                    $("html, body")
                        .stop(true, true)
                        .animate({ scrollTop: window.scrollY - offset })
                }

                const area = $element.find(".table_scrollarea")
                if (word.offset().left + word.width() > area.offset().left + area.width()) {
                    area.stop(true, true).animate({ scrollLeft: area.scrollLeft() + offset })
                } else if (word.offset().left < area.offset().left) {
                    area.stop(true, true).animate({ scrollLeft: area.scrollLeft() - offset })
                }
            }
        },
    ],
})
