import os
import sys
import subprocess

subprocess.run(["g++", "-o", "bf", "./bf.cpp"])
subprocess.run(["g++", "-o", "main", "./main.cpp"])
subprocess.run(["g++", "-o", "generator", "./generator.cpp"])

for i in range(int(sys.argv[1])):
    os.system('./generator > input.txt')
    os.system('./main < input.txt > output.txt')
    os.system('./bf < input.txt > bf_output.txt')
    if open('bf_output.txt').read().strip() != open('output.txt').read().strip():
        sys.stderr.write('Case %d: WA' % (i + 1))
        exit(0)
    else:
        sys.stderr.write('Case %d: AC\n' % (i + 1))
