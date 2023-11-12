import os
import sys
import subprocess

subprocess.run(["g++", "-o", "brute", "./brute.cpp"])
subprocess.run(["g++", "-o", "sol", "./sol.cpp"])
subprocess.run(["g++", "-o", "gen", "./gen.cpp"])

for test_case in range(int(sys.argv[1])):
    os.system('./gen ' + str(test_case) + ' > input.txt')
    os.system('./sol < input.txt > output.txt')
    os.system('./brute < input.txt > brute_output.txt')

    input = open("input.txt").readline
    output = open("output.txt").readline
    brute_output = open("brute_output.txt").readline

    def ii(input):
        return int(input())
    def li(input):
        return list(map(int, input().split()))

    for t in range(ii(input)):
        n = ii(input)
        arr = li(input)

        l_output, r_output = li(output)
        l_brute_output, r_brute_output = li(brute_output)

        sum_output = 0
        mul_output = 1
        for i in range(n):
            sum_output += arr[i]
        for i in range(l_output - 1, r_output, 1):
            sum_output -= arr[i]
            mul_output += arr[i]
        sum_output += mul_output

        sum_brute_output = 0
        mul_brute_output = 1
        for i in range(n):
            sum_brute_output += arr[i]
        for i in range(l_brute_output - 1, r_brute_output, 1):
            sum_brute_output -= arr[i]
            mul_brute_output += arr[i]
        sum_brute_output += mul_brute_output

        if sum_brute_output != sum_output:
            sys.stderr.write('Case %d: WA' % (test_case + 1))
            exit(0)
    sys.stderr.write('Case %d: AC\n' % (test_case + 1))
