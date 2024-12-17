from flask import Blueprint
from korp import utils
from flask import current_app as app
import os

bp = Blueprint("lexicon", __name__)

@bp.route("/lexicon", methods=["GET", "POST"])
@utils.main_handler
def lexicon(args):
    "Get all of the unique values of a positional attribute"
    attr = args.get("positional_attribute") or ""
    DATA_DIR = ""
    corpora = utils.parse_corpora(args)
    for corpus in corpora:
        corpus = corpus.lower()
        if(attr != "" and os.path.exists(f'{app.config["CWB_DATA"]}/{corpus}/{attr}.corpus')):
            DATA_DIR = f"{app.config['CWB_DATA']}/{corpus}/{attr}.lexicon"
        if(DATA_DIR==""):
            return {'Positional Attribute Error': 'Please specify an existing positional attribute'}
        with open(DATA_DIR, 'r') as lexicon_file:
            lines = lexicon_file.read().split("\0")
            print(lines)
            yield {'Arguments': lines}