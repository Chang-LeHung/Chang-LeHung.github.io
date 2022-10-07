

import os
import re


def scan(dir):
    files = os.listdir(dir)
    flag = False
    for file in files:
        if ".md" in file:
            flag = True
            break
    if flag and os.path.basename(dir[1:]) != "git" \
            and os.path.basename(dir[1:]) != "":
        print("*", os.path.basename(dir[1:].title()))
    subdirs = []
    for d in os.listdir(dir):
        path = os.path.join(dir, d)
        if os.path.isdir(path) and not d.startswith("."):
            subdirs.append(path)
        else:
            if d.endswith(".md") and not "READ" in d:
                with open(path, "r+") as fp:
                    content = fp.read()
                    m = re.findall(r"# (.+)", content)
                    if len(m) > 0:
                        print("\t* [", m[0], "](", path, ")")
                content = content.replace("![微信公众号](qrcode2.jpg)",
                                "![微信公众号](" + "../" * (path.count('/') - 1) + "qrcode2.jpg)")
                with open(path, "w+") as fp:
                    fp.write(content)

    for dir in subdirs:
        scan(dir)


if __name__ == '__main__':
    base_dir = "./"
    scan(base_dir)
