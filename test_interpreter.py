import glob
import interpreter
from StringIO import StringIO


def parse_test(tf, stdin):
	mode = None
	output = ''
	for line in tf:
		if line == "-@@input":
			mode = "inp"
		if line == "-@@input(no-line)":
			mode = "ipn"
		elif line == "-@@output":
			mode = "out"
		elif line == "-@@output(no-line)":
			mode = "otn"
		elif mode == "inp":
			stdin.write("%s\n" % line)
		elif mode == "ipn":
			stdin.write(line)
		elif mode == "out":
			output += "%s\n" % line
		elif mode == "otn":
			output += "%s\n" % line
	return output


for test in glob.glob("t/t*"):
	pf = open(test, "rb")
	tf = open("%s.test" % test, "rb")
	stdin = StringIO()
	stdout = StringIO()
	output = parse_test(ts, stdin)
	interpreter(pf, stdin=stdin, stdout=stdout)
	actual = stdout.getvalue()
	if output != actual:
		raise str.format(
			"{test} failed: expected:\n{expected}\nbut is:\n{result}",
			test=test,
			expected=output,
			result=stdout.getvalue()
		)
	stdin.close()
	stdout.close()