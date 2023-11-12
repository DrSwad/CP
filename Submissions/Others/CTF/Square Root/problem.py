from Crypto.Util.number import long_to_bytes as l2b, getPrime, bytes_to_long as b2l, inverse

flag = open('flag.txt', 'rb').read()

x = b2l(flag)

p = getPrime(1024)
a, b, c = getPrime(128), getPrime(128), getPrime(128)

y = (a*(x**2) + b*x + c) % p

with open('out.txt', 'w') as f:
    f.write(f"p = {p}\n")
    f.write(f"a = {a}\n")
    f.write(f"b = {b}\n")
    f.write(f"c = {c}\n")
    f.write(f"y = {y}\n")
