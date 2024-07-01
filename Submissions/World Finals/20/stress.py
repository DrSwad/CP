import sys
import os

os.system('g++ -std=c++17 gen.cpp -o gen')
os.system('g++ -std=c++17 speedlimit2.cpp -o sol')
os.system('g++ -std=c++17 brute.cpp -o brute')

for i in range(int(sys.argv[1])):
  os.system('./gen > in')
  os.system('./sol < in > out')
  os.system('./brute < in > brute_out')

  if open('out').read().strip() != open('brute_out').read().strip():
    sys.stderr.write('Case %d: WA\n' % (i + 1))
    exit(0)
  else:
    sys.stderr.write('Case %d: AC\n' % (i + 1))