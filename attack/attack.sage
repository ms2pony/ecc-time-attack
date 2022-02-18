# Config
lattice_size = 35   # number of signatures
trick = 2^128 / 2^9 # 7 leading bits

# Get data
with open(r"F:\iii\ii\i\workStudation\Studation\CTF\lattic_attack\demo2\small_nonce.txt", "r") as f:
    content = f.readlines()
f.close()
digests = []
signatures = []

# Parse it
for item in content[:lattice_size]:
    item = eval(item)
    digests.append(int(item['m']))
    signatures.append((int(item['r']), int(item['s'])))

modulo = 340282366762482138443322565580356624661

# Building Equations
nn = len(digests)
# getting rid of the first equation
r0_inv = inverse_mod(signatures[0][0], modulo)
s0 = signatures[0][1]
m0 = digests[0]
AA = [-1]
BB = [0]
for ii in range(1, nn):
    mm = digests[ii]
    rr = signatures[ii][0]
    ss = signatures[ii][1]
    ss_inv = inverse_mod(ss, modulo)

    AA_i = Mod(-1 * s0 * r0_inv * rr * ss_inv, modulo)
    BB_i = Mod(-1 * mm * ss_inv + m0 * r0_inv * rr * ss_inv, modulo)
    AA.append(AA_i.lift())
    BB.append(BB_i.lift())

# Embedding Technique (CVP->SVP)
lattice = Matrix(ZZ, nn + 1)

for ii in range(nn):
    lattice[ii, ii] = modulo
    lattice[0, ii] = AA[ii]
BB.append(trick)

lattice[nn] = vector(BB)
lattice = lattice.BKZ()

print ("found a key")
# get rid of (..., 1)
vec = list(lattice[0])
vec.pop()
vec = vector(vec)
solution = -1 * vec

# get d
rr = signatures[0][0]
ss = signatures[0][1]
mm = digests[0]
nonce = solution[0]

key = Mod((ss * nonce - mm) * inverse_mod(rr, modulo), modulo)
print(hex(key))
print(key)