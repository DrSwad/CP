from Crypto.Util.number import isPrime, inverse, long_to_bytes

p_times_q = 77877452723568809002786058317114185337930223566249526469010813218796208203291
split = 77877452723568809002786058317114185336797844222164545001194029991785424890375
p_plus_q = (p_times_q + 4 - split) // 2
cipher = 64059041051643141423589456488253364432179353193695619490257971693099941278147

# (p - 2) * (q - 2) = split
# = p * q - 2 * (p + q) + 4
# => p + q = (p * q + 4 - split) / 2

a = 1
b = -p_plus_q
c = p_times_q

# calculate the discriminant
d = (b**2) - (4*a*c)

L = 0
R = d
while R - L > 1:
  mid = (L + R) // 2
  if mid * mid <= d:
    L = mid
  else:
    R = mid

# find two solutions
p = (-b-L)//(2*a)
q = p_plus_q - p

e = 65537
l = (p - 1) * (q - 1)
d = inverse(e, l)

exp = d
a = cipher
mod = p_times_q

a %= mod

ans = 1
while exp:
  if exp % 2 == 1:
    ans = (ans * a) % mod
  a = (a * a) % mod
  exp = exp // 2

print(ans)

print(long_to_bytes(ans))