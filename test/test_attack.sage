"""
测试得到的签名样本信息是否满足等式 s = Mod(k_inv*(Hm+r*d), modulo)
modulo为曲线的n，r和s为ecdsa签名对(r,s)，k_inv为随机数k的逆，d为私钥
"""

modulo = 0xFFFFFFFE0000000075A30D1B9038A115
d = 0xc565991b6f027c664744b08071cd2c04

lattice_size = 20000
with open(r"/home/tam/github/ecc-time-attack/out/data.log", "r") as f:
    content = f.readlines()
f.close()
digests = []
signatures = []
nonces = []

# Parse it
for item in content[:lattice_size]:
    item = eval(item)
    digests.append(int(item['m']))
    signatures.append((int(item['r']), int(item['s'])))
    nonces.append(int(item['k']))

count = 0
falseList = []
for i in range(lattice_size):
    r = signatures[i][0]
    s = signatures[i][1]
    Hm = digests[i]
    k = nonces[i]
    k_inv = inverse_mod(k, modulo)
    s1 = Mod(k_inv*(Hm+r*d), modulo)
    # print(hex(s1))
    if(s1 == s):
        count += 1
    else:
        falseList.append(i+1)

print(count)
print(falseList)
