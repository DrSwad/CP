#!/usr/bin/env python3

import argparse
import subprocess as sp
import threading
from queue import Queue, Empty
import sys
import time


def intercept(out, q):
	for line in iter(out.readline, b''):
		q.put(line)
	out.close()


class ProcessThread:
	def __init__(self, cmd):
		self.p = sp.Popen(cmd, stdin=sp.PIPE, stdout=sp.PIPE, stderr=sp.PIPE, close_fds=("posix" in sys.builtin_module_names))
		self.q = dict()
		self.listen = dict()
		for stream, name in zip([self.p.stdout, self.p.stderr], ["out", "err"]):
			self.q[name] = Queue()
			self.listen[name] = threading.Thread(target=intercept, args=(stream, self.q[name]))
			self.listen[name].daemon = True
			self.listen[name].start()


	def feed_input(self, inp):
		if self.poll() is not None:
			return
		self.p.stdin.write((inp + "\n").encode())
		self.p.stdin.flush()


	def get_stream(self, stream):
    # Comment out the following two lines if race condition occurs
		if self.poll() is not None:
			return None
		lines = []
		while True:
			try:
				line = self.q[stream].get_nowait()
				lines.append(line)
			except Empty:
				break
		return None if lines == [] else "\n".join(map(lambda x: x.decode().strip(), lines))

	def get_out(self):
		return self.get_stream("out")

	def get_err(self):
		return self.get_stream("err")

	def poll(self):
		return self.p.poll()


color_codes = {
	"Reset": 0,
	"Bold": 1,
	"Underline": 2,
	"Inverse": 7,
	"Black": 30,
	"Red": 31,
	"Green": 32,
	"Yellow": 33,
	"Blue": 34,
	"Magenta": 35,
	"Cyan": 36,
	"White": 37,
}

def colored(text, color):
	if color not in color_codes:
		return text
	return f"\033[{color_codes[color]}m{text}\033[0m"


def print_framed(text, left_appendix="", right_appendix="", color="normal"):
	color = color.capitalize()
	lines = text.strip().split('\n')
	width = max(map(len, lines)) + 2
	print(colored(" " * len(left_appendix) + "+" + "-" * width + "+", color))
	for line in lines:
		print(colored(" " * len(left_appendix) + "| ", color) + line.ljust(width - 2, ' ') + colored(" |", color))
	print(colored(left_appendix + "+" + "-" * width + "+" + right_appendix, color))


parser = argparse.ArgumentParser(description="Make two programs interact with each other.")
parser.add_argument("solution", metavar="<solution exec>", help="Executable file of the solution to test")
parser.add_argument("interactor", metavar="<interactor exec>", help="Executable file of the interactor to test your solution against.")
parser.add_argument("-c", "--color", action="store_true", help="Colored frames")
parser.add_argument("--no-stderr", action="store_true", help="Disable stderr printing")
parser.add_argument("--hang-timeout", type=float, default=1, help="The number of seconds to wait for the solution to exit after the interactor has finished")

args = parser.parse_args()

solution = ProcessThread(args.solution)
interactor = ProcessThread(args.interactor)

solution_running = True
interactor_running = True

hanging_start = None
HANG_TIMEOUT = args.hang_timeout

while True:
	if solution_running and solution.poll() != None:
		print(f"Solution process exited with error code {solution.poll()}")
		solution_running = False
	if interactor_running and interactor.poll() != None:
		print(f"Interactor process exited with error code {interactor.poll()}")
		interactor_running = False
	if not solution_running and not interactor_running:
		break
	if solution_running and not interactor_running:
		if hanging_start is None:
			hanging_start = time.time()
		if time.time() - hanging_start >= HANG_TIMEOUT:
			print(f"Solution process has been forced to shut down due to timeout")
			sys.exit(0)


	soln_out = solution.get_out()
	inter_out = interactor.get_out()
	soln_err = solution.get_err()
	inter_err = interactor.get_err()

	if soln_out is not None:
		print_framed(soln_out, "solution: ", "", "green" if args.color else "")
		interactor.feed_input(soln_out)
		hanging_start = None
	if soln_err is not None and not args.no_stderr:
		print_framed(soln_err, "  stderr: ", "", "yellow" if args.color else "")
		hanging_start = None
	if inter_out is not None:
		print_framed(inter_out, "          ", " :interactor", "cyan" if args.color else "")
		solution.feed_input(inter_out)
	if inter_err is not None and not args.no_stderr:
		print_framed(inter_err, "          ", " :interactor stderr", "red" if args.color else "")
