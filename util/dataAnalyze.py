# 签名r,s ；哈希值m ；消耗时间t；对应的临时随机数k；k的为数：len
# 一共六项
newContent=""
newContents=[]
with open("/home/tam/github/easy-ecc/t1/out/nonces.log","r") as f:
    lines=f.readlines()
    for line in lines:
        # print(line)
        newContent='"k":'+line.strip()+','
        newContent+='"len":'+str(len(bin(int(line,16)))-2)+','
        # print(newContent)
        newContents.append(newContent)

# print(newContents)

newContent1=""
newContent1s=[]
with open("/home/tam/github/easy-ecc/t1/out/sign.log","r") as f:
    lines=f.readlines()
    for line in lines:
        elms=line.strip().split(",")
        # print(elms)
        newContent1='"r":'+elms.pop(0)+','
        newContent1+='"s":'+elms.pop(0)+','
        newContent1+='"t":'+elms.pop(0)+','
        newContent1+='"m":'+elms.pop(0)+','
        newContent1=newContent1[0:-1]
        newContent1s.append(newContent1)

e=""
content=""
for e1, e2 in zip(newContents,newContent1s):
    e=e1+e2
    e="{"+e+"}"+"\n"
    content+=e

content=content[0:-1]



with open("/home/tam/github/easy-ecc/t1/out/data.log","w") as f:
    f.write(content)