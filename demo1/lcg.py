"""
"""
# python
from Crypto.Util.number import *
from Crypto.Cipher import AES


class LCG:
    def __init__(self, bit_length):
        b = 153582801876235638173762045261195852087
        a = 107763262682494809191803026213015101802
        m = 226649634126248141841388712969771891297
        seed = 73991202721494681711496408225724067994
        self._key = {'a': a, 'b': b, 'm': m}
        self._state = seed

    # LCG生成随机数
    def next(self):
        self._state = (self._key['a'] * self._state +
                       self._key['b']) % self._key['m']
        return self._state

    def export_key(self):
        return self._key


def gen_lcg():
    rand_iter = LCG(128)
    key = rand_iter.export_key()
    f = open("key", "w")
    f.write(str(key))
    return rand_iter


def leak_data(rand_iter):
    f = open("old", "w")
    for i in range(20):
        f.write(str(rand_iter.next() >> 64) + "n")
    return rand_iter


def encrypt(rand_iter):
    f = open("ct", "wb")
    key = rand_iter.next() >> 64
    key = (key << 64) + (rand_iter.next() >> 64)
    key = long_to_bytes(key).ljust(16, b'x00')
    iv = long_to_bytes(rand_iter.next()).ljust(16, b'x00')
    cipher = AES.new(key, AES.MODE_CBC, iv)
    pt = flag + (16 - len(flag) % 16) * chr(16 - len(flag) % 16)
    ct = cipher.encrypt(pt.encode())
    f.write(ct)


def decrypt(rand_iter):
    with open("ct", "rb") as f:
        flag = f.read()

    key = rand_iter.next() >> 64
    key = (key << 64) + (rand_iter.next() >> 64)
    key = long_to_bytes(key).ljust(16, b'x00')
    iv = long_to_bytes(rand_iter.next()).ljust(16, b'x00')
    cipher = AES.new(key, AES.MODE_CBC, iv)
    ct = cipher.decrypt(flag)
    print(ct)


def main():
    rand_iter = gen_lcg()
    # rand_iter = leak_data(rand_iter)
    # decrypt(rand_iter)
    print(rand_iter.next())


if __name__ == "__main__":
    main()
