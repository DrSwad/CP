#!/usr/bin/env python3

"""
Local testing tool for Riddle of the Sphinx.

Note: This tool is intended to help with debugging interaction.
It is *not* the same code used to test your solution when it
is submitted. For example, the tool *does not* apply the time
and memory limits that are applied to submitted solutions,
and there may be other differences, especially if your solution
exhibits incorrect behavior.

This testing tool implements a sphinx which never lies.

To run the testing tool, run::

    ./testing_tool.py <la> <lb> <lc> <program> <arguments>

where `arguments` are optional arguments to the program to run. The following
show examples for different languages::

    ./testing_tool.py 4 4 4 ./myprogram
    ./testing_tool.py 4 4 4 java -cp . MyProgram
    ./testing_tool.py 4 4 4 pypy3 myprogram.py
"""

import argparse
import subprocess
import sys
from typing import TextIO



class WrongAnswer(RuntimeError):
    """Raised whenever an incorrect answer is received."""
    pass

def vprint(*args, verbose: bool, file: TextIO, **kwargs) -> None:
    """Print to `file`, and also to stdout if `verbose is true."""
    if verbose:
        print('< ', end='')
        print(*args, **kwargs)
        sys.stdout.flush()
    print(*args, file=file, **kwargs)


def vreadline(data: TextIO, verbose: bool) -> str:
    """Read a line from `data`, and also log it to stdout if `verbose` is true."""
    line = data.readline()
    if verbose and line:
        print('>', line.rstrip('\n'))
    return line


def answer_question(process: subprocess.Popen, la: int, lb: int, lc: int) -> None:
    """Read a question from the solution and provide the answer."""
    line = vreadline(process.stdout, True)
    if line == '':
        raise WrongAnswer('End of file received from team program')
    tokens = line.split()
    if len(tokens) != 3:
        raise WrongAnswer('Invalid question, did not contain three tokens')
    try:
        question = [int(x) for x in tokens]
    except ValueError:
        raise WrongAnswer('Question contains non-integer tokens')
    if any(not (0 <= q <= 10) for q in question):
        raise WrongAnswer('Invalid question value not between 0 and 10')
    answer = question[0] * la + question[1] * lb + question[2] * lc
    vprint(str(answer), file=process.stdin, flush=True, verbose=True)

    
def check_answer(process: subprocess.Popen, la: int, lb: int, lc: int) -> None:
    """Read and check the final answer provided by the program."""
    line = vreadline(process.stdout, True)
    if line == '':
        raise WrongAnswer('End of file received from team program')
    tokens = line.split()
    if len(tokens) != 3:
        raise WrongAnswer('Invalid final answer, did not contain three tokens')
    try:
        answer = [int(x) for x in tokens]
    except ValueError:
        raise WrongAnswer('Final answer contains non-integer tokens')
    if answer[0] != la or answer[1] != lb or answer[2] != lc:
        raise WrongAnswer('Wrong final answer provided')


def check_done(process: subprocess.Popen) -> None:
    """Check for extra output from program."""
    line = vreadline(process.stdout, True)
    if line != '':
        raise WrongAnswer('Program gave extra output')


def main() -> int:
    parser = argparse.ArgumentParser(usage='%(prog)s [-h] la lb lc program [args...]')
    parser.add_argument('la', type=int, help='number of legs of an Axex')
    parser.add_argument('lb', type=int, help='number of legs of a Basilisk')
    parser.add_argument('lc', type=int, help='number of legs of a Centaur')
    parser.add_argument('program', nargs=argparse.REMAINDER)

    args = parser.parse_args()
    if not args.program:
        parser.error('Must specify program to run')

    process = subprocess.Popen(args.program, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                               encoding='utf-8', errors='surrogateescape')
    try:
        for _ in range(5):
            answer_question(process, args.la, args.lb, args.lc)
        check_answer(process, args.la, args.lb, args.lc)
        check_done(process)
        print(f'OK! Program found the correct number of legs of all three creatures')
    except WrongAnswer as e:
        print('ERROR: %s' % e)
        return 1
    except BrokenPipeError:
        print('ERROR: error when communicating with program - exited prematurely?')
        return 2
    
    return 0


if __name__ == '__main__':
    sys.exit(main())
