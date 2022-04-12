# sage
b = 153582801876235638173762045261195852087
a = 107763262682494809191803026213015101802
m = 226649634126248141841388712969771891297

h = [0, 7800489346663478448, 11267068470666042741, 5820429484185778982, 6151953690371151688, 548598048162918265, 1586400863715808041, 7464677042285115264, 4702115170280353188, 5123967912274624410, 8517471683845309964,
     2106353633794059980, 11042210261466318284, 4280340333946566776, 6859855443227901284, 3149000387344084971, 7055653494757088867, 5378774397517873605, 8265548624197463024, 2898083382910841577, 4927088585601943730]
for i in range(len(h)):
    h[i] <<= 64
A = [1]
B = [0]
for i in range(1, len(h)-1):
    A.append(a*A[i-1] % m)
    B.append((a*B[i-1]+a*h[i]+b-h[i+1]) % m)
A = A[1:]
B = B[1:]


M = matrix(ZZ, 21, 21)

for i in range(19):
    M[i, i] = m
    M[19, i] = A[i]
    M[20, i] = B[i]
    M[i, 19] = M[i, 20] = 0
M[19, 19] = 1
M[20, 20] = 2 ^ 64
M[19, 20] = 0

vl = M.LLL()[0]
l1 = vl[-2]
h1 = h[1]
s1 = l1+h1
#s1 = a*seed+b %m
seed = ((s1 - b)*inverse_mod(a, m)) % m
print(seed)
