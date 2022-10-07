

import os
import re


def scan(dir):
    for d in os.listdir(dir):
        path = os.path.join(dir, d)
        if os.path.isdir(path) and not d.startswith("."):
            scan(path)
        else:
            if d.endswith(".md") :
                with open(path, "r+") as fp:
                    content = fp.read()
                    m = re.findall(r"# (.+)", content)
                    if len(m) > 0:
                        print("[", m[0], "](", path, ")")
                content = content.replace("![微信公众号](qrcode2.jpg)",
                                "![微信公众号](" + "../" * (path.count('/') - 1) + "qrcode2.jpg)")
                with open(path, "w+") as fp:
                    fp.write(content)


if __name__ == '__main__':
    base_dir = "./"
    scan(base_dir)
