from flask import Blueprint, request, jsonify

from korp import utils
from html.parser import HTMLParser
import re

n_fields = 15
class MyHTMLParser(HTMLParser):
    def __init__(self, fo):
        super().__init__()
        self.fo = fo
        self.buf = ''
        self.sentence_id = 1
        self.word_tokens = 0

    def handle_data(self, data):
        for sentence in re.split('([!?.]+)', data):
            sentence = sentence.strip()
            if not sentence: continue
            self.buf += sentence
            if self.buf[-1] in '.!?':
                self.process_sentence(self.buf)
                self.buf = ''

    def process_sentence(self, sentence):
        fo.write(f'<sentence id="{self.sentence_id}">\n')
        word_id = 1
        for word in re.split(r'([ .!?,:;\"\'\(\)])', sentence):
            word = word.strip()
            if not word: continue
            line = word
            fo.write(f'{word}\t{word_id}\t{self.word_tokens}-{self.word_tokens+len(word)}'+"\t_"*(n_fields-3) + "\n")
            self.word_tokens += len(word) + 1
            word_id += 1
        fo.write(f'</sentence>\n')
        self.sentence_id += 1

bp = Blueprint("genvrt", __name__)


@bp.route("/genvrt", methods=["GET", "POST"])
@utils.main_handler
def genvrt(args):
    uploaded_file = request.files.get('input')

    output = app.config["CWB_VRTS"] + "/" + (uploaded_file.filename + ".vrt")
    with open(output, 'x') as fo:
        fo.write(f'<corpus>\n')
        fo.write(f'<text id="text_1">\n')
        parser = MyHTMLParser(fo)
        parser.feed(uploaded_file)
        fo.write(f'</text>\n')
        fo.write(f'</corpus>\n')

    result = {"file_size": len(uploaded_file)}
    return jsonify(result)
