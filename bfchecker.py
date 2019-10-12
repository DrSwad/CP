import os
import sys

for i in range(100):
    # os.system('./generator ' + str(seed) + ' > input.txt')
    os.system('./generator > in')
    # open("in", "w").write(str(i)
    os.system('./bf < in > bfout')
    os.system('./main < in > out')
    if open('bfout').read() != open('out').read():
            sys.stderr.write('Case %d: WA' % (i + 1))
            exit(0)
    else:
        sys.stderr.write('Case %d: AC\n' % (i + 1))
