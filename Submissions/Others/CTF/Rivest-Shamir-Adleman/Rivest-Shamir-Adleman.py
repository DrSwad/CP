from Crypto.Util.number import getPrime, inverse, bytes_to_long

with open('flag.txt', 'r') as file:
    message = file.read()


message_bytes = message.encode()

bit_length = 128
p = getPrime(bit_length)
q = getPrime(bit_length)


n = p * q
l = (p - 1) * (q - 1)
e = 65537
d = inverse(e, l)

message_int = bytes_to_long(message_bytes)
ciphertext = pow(message_int, e, n)

split = (p - 2) * (q - 2)
print('cipher:', ciphertext)
print('n:', n)
print('e:', e)
print('split:',split)
