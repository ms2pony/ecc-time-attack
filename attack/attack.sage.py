

# This file was *autogenerated* from the file attack.sage
from sage.all_cmdline import *   # import sage library

_sage_const_60 = Integer(60); _sage_const_1 = Integer(1); _sage_const_0xFFFFFFFE0000000075A30D1B9038A115 = Integer(0xFFFFFFFE0000000075A30D1B9038A115); _sage_const_0 = Integer(0)# Config
lattice_size = _sage_const_60    # number of signatures
# trick = 2 ^ 128 / 2 ^ 12  # 7 leading bits
trick = _sage_const_1   # 7 leading bits
modulo = _sage_const_0xFFFFFFFE0000000075A30D1B9038A115   # 该ecdsa的参数n

# Get data
# with open(r"/home/tam/github/ecc-time-attack/out/small_nonce.txt", "r") as f:
with open(r"/home/tam/github/ecc-time-attack/out/small_cycle.txt", "r") as f:
    content = f.readlines()
f.close()
digests = []
signatures = []

# Parse it
for item in content[:lattice_size]:
    item = eval(item)
    digests.append(int(item['m']))
    signatures.append((int(item['r']), int(item['s'])))

# Building Equations
nn = lattice_size

# getting rid of the first equation
r0_inv = inverse_mod(signatures[_sage_const_0 ][_sage_const_0 ], modulo)
s0 = signatures[_sage_const_0 ][_sage_const_1 ]
m0 = digests[_sage_const_0 ]
AA = [-_sage_const_1 ]
BB = [_sage_const_0 ]  # B_{0}=0
for ii in range(_sage_const_1 , nn):
    mm = digests[ii]
    rr = signatures[ii][_sage_const_0 ]
    ss = signatures[ii][_sage_const_1 ]
    ss_inv = inverse_mod(ss, modulo)

    AA_i = Mod(-_sage_const_1  * s0 * r0_inv * rr * ss_inv, modulo)
    BB_i = Mod(-_sage_const_1  * mm * ss_inv + m0 * r0_inv * rr * ss_inv, modulo)
    AA.append(AA_i.lift())
    BB.append(BB_i.lift())


# Embedding Technique (CVP->SVP)
lattice = Matrix(ZZ, nn + _sage_const_1 )
# print(lattice[0])


for ii in range(nn):
    lattice[ii, ii] = modulo
    lattice[_sage_const_0 , ii] = AA[ii]
BB.append(trick)

# print(lattice[0])
lattice[nn] = vector(BB)
lattice = lattice.BKZ()

# print("found a key")
# get rid of (..., 1)
vec = list(lattice[_sage_const_0 ])
vec.pop()
vec = vector(vec)
solution = -_sage_const_1  * vec

# get d
rr = signatures[_sage_const_0 ][_sage_const_0 ]
ss = signatures[_sage_const_0 ][_sage_const_1 ]
mm = digests[_sage_const_0 ]
nonce = solution[_sage_const_0 ]

key = Mod((ss * nonce - mm) * inverse_mod(rr, modulo), modulo)
print(hex(key))

