from flask import Blueprint, request, send_file, after_this_request
from flask import current_app as app

from korp import utils
from html.parser import HTMLParser
import re
import os

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
        self.fo.write(f'<sentence id="{self.sentence_id}">\n')
        word_id = 1
        for word in re.split(r'([ .!?,:;\"\'\(\)])', sentence):
            word = word.strip()
            if not word: continue
            line = word
            self.fo.write(f'{word}\t{word_id}\t{self.word_tokens}-{self.word_tokens+len(word)}'+"\t_"*(n_fields-3) + "\n")
            self.word_tokens += len(word) + 1
            word_id += 1
        self.fo.write(f'</sentence>\n')
        self.sentence_id += 1

bp = Blueprint("genvrt", __name__)


@bp.route("/genvrt", methods=["GET", "POST"])
def genvrt():
    uploaded_file = request.files.get('vrt')
    tempFile = app.config["CWB_VRTS"] + "/" + uploaded_file.filename
    uploaded_file.save(tempFile)
    
    fileNameWithoutExtension = uploaded_file.filename[:uploaded_file.filename.index(".")]
    output = app.config["CWB_VRTS"] + "/" + (fileNameWithoutExtension + ".vrt")
    with open(tempFile, 'r') as tempFileRead:
        with open(output, 'x') as fo:
            fo.write(f'<corpus>\n')
            fo.write(f'<text id="text_1">\n')
            parser = MyHTMLParser(fo)
            parser.feed(tempFileRead.read())
            fo.write(f'</text>\n')
            fo.write(f'</corpus>\n')
    
    @after_this_request
    def remove_file(response):
        try:
            os.remove(output)
            os.remove(tempFile)
        except Exception as error:
            app.logger.error("Error removing or closing downloaded file handle", error)
        return response
    
    return send_file(output, as_attachment=True)
