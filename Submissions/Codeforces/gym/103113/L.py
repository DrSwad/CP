EXP = 60
p = []
inv_p = []

def lsb(n):
  assert n > 0
  for i in range(EXP):
    if (n & (1 << i)) != 0:
      return i
  assert False

def init():
  global p
  global inv_p

  print(EXP + (EXP - 1))
  p.append("R0")
  for i in range(1, EXP, 1):
    p.append("R" + str(i))
    print(f"S({p[i - 1]}, {p[i - 1]})")
  inv_p.append("R0")
  for i in range(1, EXP, 1):
    inv_p.append("R" + str(EXP + i - 1))
    print(f"P({inv_p[i - 1]}, {inv_p[i - 1]})")
  print("", flush=True, end="")

init()

def serial(up, down):
  assert up > 0 and down > 0
  q = up // down
  r = up % down
  assert q != 0 or r != 0
  if (q == 0):
    parallel_frac(up, down)
  elif (r == 0):
    l = lsb(q)
    if (q == 1 << l):
      print(p[l], end="")
    else:
      print(f"S({p[l]}, ", end="")
      serial(q - (1 << l), 1)
      print(")", end="")
  else:
    print(f"S(", end="")
    serial(q, 1)
    print(", ", end="")
    parallel_frac(r, down)
    print(")", end="")

def parallel_int(val):
  assert val > 0
  l = lsb(val)
  if val == 1 << l:
    print(inv_p[l], end="")
  else:
    print(f"P({inv_p[l]}, ", end="")
    parallel_int(val - (1 << l))
    print(")", end="")

def parallel_frac(up, down):
  assert up > 0 and down > 0
  assert up < down

  up, down = down, up

  q = up // down
  r = up % down
  assert q != 0

  if r == 0:
    assert q > 1
    print(f"P(", end="")
    parallel_int(1)
    print(", ", end="")
    parallel_int(q - 1)
    print(f")", end="")
  else:
    print("P(", end="")
    parallel_int(q)
    print(", ", end="")
    serial(down, r)
    print(")", end="")

q = int(input())
for _ in range(q):
  up, down = map(int, input().split())
  serial(up, down)
  print("", flush=True)