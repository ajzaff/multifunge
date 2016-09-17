from __future__ import print_function
import glob
import interpreter
from StringIO import StringIO
import signal
import sys
from contextlib import contextmanager


def parse_test(tf, stdin):
	mode = None
	output = ''
	desc = tf.name
	tmt = 1000
	for line in tf:
		if line == "-@timeout":
			mode = "tmt"
		if line == "-@desc":
			mode = "dsc"
		if line == "-@input":
			mode = "inp"
		if line == "-@input(no-line)":
			mode = "ipn"
		elif line == "-@output":
			mode = "out"
		elif line == "-@output(no-line)":
			mode = "otn"
		elif mode == "tmt":
			tmt = int(line)
			mode = ""
		elif mode == "nam":
			name = line
			mode = ""
		elif mode == "desc":
			desc = line
			mode = ""
		elif mode == "inp":
			stdin.write("%s\n" % line)
		elif mode == "ipn":
			stdin.write(line)
			mode = ""
		elif mode == "out":
			output += "%s\n" % line
		elif mode == "otn":
			output += "%s\n" % line
			mode = ""
	return tmt, desc, output


#################
#Credit: Josh Lee
#http://stackoverflow.com/questions/366682/how-to-limit-execution-time-of-a-function-call-in-python

class TimeoutException(Exception): pass

@contextmanager
def time_limit(seconds):
    def signal_handler(signum, frame):
        raise TimeoutException, "Timed out!"
    signal.signal(signal.SIGALRM, signal_handler)
    signal.alarm(seconds)
    try:
        yield
    finally:
        signal.alarm(0)
		
##

if __name__ == "__main__":
	for test in glob.glob("./t/t*"):
		if test.endswith(".test"):
			continue
		tf = open("%s.test" % test, "rb")
		stdin = StringIO()
		stdout = StringIO()
		tmt, desc, output = parse_test(tf, stdin)
		with time_limit(tmt):
			interpreter.main(test, input=stdin, output=stdout)
		actual = stdout.getvalue()
		if output != actual:
			print(u"\u2718", desc, sep="\t")
			raise str.format(
				"{test} failed: expected:\n{expected}\nbut is:\n{result}",
				test=pf.name,
				expected=output,
				result=stdout.getvalue()
			)
			sys.exit(1)
		else:
			print(u"\u2713", desc, sep="\t")
		stdin.close()
		stdout.close()
		sys.exit()