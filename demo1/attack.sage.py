

# This file was *autogenerated* from the file attack.sage
from sage.all_cmdline import *   # import sage library

_sage_const_153582801876235638173762045261195852087 = Integer(153582801876235638173762045261195852087); _sage_const_107763262682494809191803026213015101802 = Integer(107763262682494809191803026213015101802); _sage_const_226649634126248141841388712969771891297 = Integer(226649634126248141841388712969771891297); _sage_const_0 = Integer(0); _sage_const_7800489346663478448 = Integer(7800489346663478448); _sage_const_11267068470666042741 = Integer(11267068470666042741); _sage_const_5820429484185778982 = Integer(5820429484185778982); _sage_const_6151953690371151688 = Integer(6151953690371151688); _sage_const_548598048162918265 = Integer(548598048162918265); _sage_const_1586400863715808041 = Integer(1586400863715808041); _sage_const_7464677042285115264 = Integer(7464677042285115264); _sage_const_4702115170280353188 = Integer(4702115170280353188); _sage_const_5123967912274624410 = Integer(5123967912274624410); _sage_const_8517471683845309964 = Integer(8517471683845309964); _sage_const_2106353633794059980 = Integer(2106353633794059980); _sage_const_11042210261466318284 = Integer(11042210261466318284); _sage_const_4280340333946566776 = Integer(4280340333946566776); _sage_const_6859855443227901284 = Integer(6859855443227901284); _sage_const_3149000387344084971 = Integer(3149000387344084971); _sage_const_7055653494757088867 = Integer(7055653494757088867); _sage_const_5378774397517873605 = Integer(5378774397517873605); _sage_const_8265548624197463024 = Integer(8265548624197463024); _sage_const_2898083382910841577 = Integer(2898083382910841577); _sage_const_4927088585601943730 = Integer(4927088585601943730); _sage_const_64 = Integer(64); _sage_const_1 = Integer(1); _sage_const_21 = Integer(21); _sage_const_19 = Integer(19); _sage_const_20 = Integer(20); _sage_const_2 = Integer(2)# sage
b = _sage_const_153582801876235638173762045261195852087 
a = _sage_const_107763262682494809191803026213015101802 
m = _sage_const_226649634126248141841388712969771891297 

h = [_sage_const_0 , _sage_const_7800489346663478448 , _sage_const_11267068470666042741 , _sage_const_5820429484185778982 , _sage_const_6151953690371151688 , _sage_const_548598048162918265 , _sage_const_1586400863715808041 , _sage_const_7464677042285115264 , _sage_const_4702115170280353188 , _sage_const_5123967912274624410 , _sage_const_8517471683845309964 ,
     _sage_const_2106353633794059980 , _sage_const_11042210261466318284 , _sage_const_4280340333946566776 , _sage_const_6859855443227901284 , _sage_const_3149000387344084971 , _sage_const_7055653494757088867 , _sage_const_5378774397517873605 , _sage_const_8265548624197463024 , _sage_const_2898083382910841577 , _sage_const_4927088585601943730 ]
for i in range(len(h)):
    h[i] <<= _sage_const_64 
A = [_sage_const_1 ]
B = [_sage_const_0 ]
for i in range(_sage_const_1 , len(h)-_sage_const_1 ):
    A.append(a*A[i-_sage_const_1 ] % m)
    B.append((a*B[i-_sage_const_1 ]+a*h[i]+b-h[i+_sage_const_1 ]) % m)
A = A[_sage_const_1 :]
B = B[_sage_const_1 :]


M = matrix(ZZ, _sage_const_21 , _sage_const_21 )

for i in range(_sage_const_19 ):
    M[i, i] = m
    M[_sage_const_19 , i] = A[i]
    M[_sage_const_20 , i] = B[i]
    M[i, _sage_const_19 ] = M[i, _sage_const_20 ] = _sage_const_0 
M[_sage_const_19 , _sage_const_19 ] = _sage_const_1 
M[_sage_const_20 , _sage_const_20 ] = _sage_const_2  ** _sage_const_64 
M[_sage_const_19 , _sage_const_20 ] = _sage_const_0 

vl = M.LLL()[_sage_const_0 ]
l1 = vl[-_sage_const_2 ]
h1 = h[_sage_const_1 ]
s1 = l1+h1
#s1 = a*seed+b %m
seed = ((s1 - b)*inverse_mod(a, m)) % m
print(seed)
