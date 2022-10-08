

import os
import re
import cn2an

cnt = 1


def scan(dir):
    global cnt
    files = os.listdir(dir)
    flag = False
    for file in files:
        if ".md" in file:
            flag = True
            break
    if flag and os.path.basename(dir[1:]) != "git" \
            and os.path.basename(dir[1:]) != "":
        print("*", "第" + cn2an.an2cn(str(cnt), "low") + "章. " + os.path.basename(dir[1:].title()))
        cnt += 1
    subdirs = []
    lcnt = 1
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
                        print("\t* [第" + cn2an.an2cn(str(lcnt), "low") + "节. " + m[0] + "](", path, ")")
                        lcnt += 1
                # content = content.replace("![微信公众号](qrcode2.jpg)",
                #                 "![微信公众号](" + "../" * (path.count('/') - 1) + "qrcode2.jpg)")
                # with open(path, "w+") as fp:
                #     fp.write(content)

    for dir in subdirs:
        scan(dir)


if __name__ == '__main__':
    base_dir = "./"
    scan(base_dir)
