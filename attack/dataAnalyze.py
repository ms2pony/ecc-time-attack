# 签名r,s ；哈希值m ；消耗时间t；对应的临时随机数k；k的为数：len
# 一共六项

def getData():
    """
    生成data.log文件
    """
    newContent = ""
    newContents = []
    with open("../out/temp/nonces.log", "r") as f:
        lines = f.readlines()
        for line in lines:
            # print(line)
            newContent = '"k":'+line.strip()+','
            newContent += '"len":'+str(len(bin(int(line, 16)))-2)+','
            # print(newContent)
            newContents.append(newContent)

    # print(newContents)

    newContent1 = ""
    newContent1s = []
    with open("../out/temp/sign.log", "r") as f:
        lines = f.readlines()
        for line in lines:
            elms = line.strip().split(",")
            # print(elms)
            newContent1 = '"r":'+elms.pop(0)+','
            newContent1 += '"s":'+elms.pop(0)+','
            newContent1 += '"t":'+elms.pop(0)+','
            newContent1 += '"m":'+elms.pop(0)+','
            newContent1 = newContent1[0:-1]
            newContent1s.append(newContent1)

    e = ""
    content = ""
    for e1, e2 in zip(newContents, newContent1s):
        e = e1+e2
        e = "{"+e+"}"+"\n"
        content += e

    content = content[0:-1]

    with open("../out/data.log", "w") as f:
        f.write(content)


def getRank():
    """
    生成small_cycle.txt和small_nonce.txt文件
    """
    # 取前100个签名时间最短的数据存入small_cycle.txt中
    with open("../out/data.log", "r") as f:
        infos = []
        lines = f.readlines()
        for line in lines:
            infos.append(eval(line))

        infos.sort(key=lambda info: info['t'])

    with open("../out/small_cycle.txt", "w") as f:
        for info in infos[0:100]:
            f.writelines(str(info)+"\n")

    # 取前100个临时随机数最小的数据存入small_nonce.txt中
    with open("../out/data.log", "r") as f:
        infos = []
        lines = f.readlines()
        for line in lines:
            infos.append(eval(line))

        infos.sort(key=lambda info: info['len'])

    with open("../out/small_nonce.txt", "w") as f:
        for info in infos[0:100]:
            f.writelines(str(info)+"\n")


if __name__ == '__main__':
    getData()
    getRank()
