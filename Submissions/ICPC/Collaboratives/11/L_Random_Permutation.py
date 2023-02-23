from decimal import *
getcontext().prec = 100

n = int(input())
N = Decimal(n)

ans = Decimal(1.0)
for i in range(1, n + 1):
  ans *= Decimal(i)**2

ans /= N**N

print("{:.28f}".format(ans))