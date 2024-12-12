from flask import Blueprint, request, jsonify
import subprocess
from korp import utils
from flask import current_app as app
import os

bp = Blueprint("upload", __name__)

@bp.route("/upload", methods=["GET", "POST"])
def upload():
    # TODO: kui uploadid ja puudub config kaust, tekita selle
    uploaded_file = request.files.get('corpus')
    #if os.path.exists(app.config["CWB_VRTS"] + "/" + uploaded_file.filename):
    #    return jsonify({
    #        "message": "juba olmas"
    #    })
    uploaded_file.save(app.config["CWB_VRTS"] + "/" + uploaded_file.filename)
    fileName = uploaded_file.filename[:uploaded_file.filename.index(".")]
    cwb = [f"cwb-encode -d {app.config["CWB_DATA"]} -f {app.config["CWB_VRTS"] + "/" + uploaded_file.filename} -R {app.config["CWB_REGISTRY"] + "/" + fileName}"]
    with open(app.config["CWB_VRTS"] + "/" + uploaded_file.filename, 'r') as vrtFile:
        pAttrs = vrtFile.readline()[1:].split()
        configPath = "./config/attributes/positional"
        # generating positional attribute yaml files
        for pAttr in pAttrs:
            if pAttr == "word": continue
            if os.path.exists(f"{configPath}/{pAttr}.yaml"): continue
            with open(f"{configPath}/{pAttr}.yaml", 'w') as pAttrYaml:
                pAttrYaml.write(f"label: {pAttr}")
        sAttrs = {}
        for line in vrtFile.readlines():
            if line[0] != '<': continue
            sAttr = line.split()

            # check if structural attr has id
            if len(sAttr) == 1: sAttr = sAttr[0][1:-1]
            else: sAttr = sAttr[0][1:]

            if sAttr[0] != "/": # check for closing tag
                if sAttr in sAttrs:
                    sAttrs[sAttr] += 1
                    sAttrs[sAttr+"_max"] = max(sAttrs[sAttr+"_max"], sAttrs[sAttr])
                else:
                    sAttrs[sAttr] = 1
                    sAttrs[sAttr+"_max"] = 1
            else:
                sAttrs[sAttr[1:]] -= 1

        # generating corpus yaml file
        configPath = "./config/corpora"
        with open(f"{configPath}/{fileName}.yaml", 'w') as corpusYaml:
            corpusYaml.write(f"id: {fileName}\ntitle: {fileName}\ndescription: {fileName}\nmode:\n  - name: default\nwithin:\n")
            # write within
            for sAttr in sAttrs:
                if "max" in sAttr: continue
                for i in range(sAttrs[sAttr+"_max"]):
                    if i == 0:
                        corpusYaml.write(f"  - label:\n      eng: {sAttr}\n    value: {sAttr}\n")
                    else:
                        corpusYaml.write(f"  - label:\n      eng: {sAttr+str(i)}\n    value: {sAttr+str(i)}\n")
            corpusYaml.write("context:\n")
            # write context
            for sAttr in sAttrs:
                if "max" in sAttr: continue
                contextLength = 1
                sAttrMax = sAttrs[sAttr+"_max"]
                if sAttrMax > 1: cwb.append(f"-S {sAttr}:{sAttrMax-1}")
                else: cwb.append(f"-S {sAttr}")
                if sAttr == "sentence":
                    contextLength = 2
                for i in range(sAttrMax):
                    for j in range(contextLength):
                        if i == 0:
                            corpusYaml.write(f"  - label:\n      eng: {j} {sAttr}\n    value: {j} {sAttr}\n")
                        else:
                            corpusYaml.write(f"  - label:\n      eng: {j} {sAttr+str(i)}\n    value: {j} {sAttr+str(i)}\n")

            corpusYaml.write("pos_attributes:\n")
            for pAttr in pAttrs:
                if pAttr == "word": continue
                corpusYaml.write(f"  - {pAttr}: {pAttr}\n")
                cwb.append(f"-P {pAttr}")

        sAttrs = set(filter(lambda sAttr: "max" not in sAttr ,sAttrs.keys()))
        sAttrs.remove("text")
        sAttrs.remove("corpus")

        # generating structural attribute yaml files
        configPath = "./config/attributes/structural"
        for sAttr in sAttrs:
            if os.path.exists(f"{configPath}/{sAttr}.yaml"): continue
            with open(f"{configPath}/{sAttr}.yaml", 'w') as sAttrYaml:
                sAttrYaml.write(f"label: {sAttr}\nvalue: {sAttr}")
        
        cwb.append("-c utf8")
        command = " ".join(cwb)
        try:
            result = subprocess.run(command, shell=True, check=True, text=True, capture_output=True)
            command = f"cwb-makeall -r {app.config["CWB_REGISTRY"]} {fileName}"
            result = subprocess.run(command, shell=True, check=True, text=True, capture_output=True)
        except subprocess.CalledProcessError as e:
            print("error")
            print(e)

    return jsonify({
        "message": "wow töötab"
    })