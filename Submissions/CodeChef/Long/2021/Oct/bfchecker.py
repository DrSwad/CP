import sys

if open('bout.txt').read().strip() != open('out.txt').read().strip():
  sys.stderr.write('WA')
else:
  sys.stderr.write('AC')
