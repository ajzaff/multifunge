from __future__ import print_function
import random
import sys


DEBUG = False


if len(sys.argv) < 2:
	print("usage: %s <PROGRAM>" % sys.argv[0])
	sys.exit(1)

nlines = 0
linel = 0
m = {}
with open(sys.argv[1], "rb") as f:
	lines = f.readlines()
	nlines = len(lines)
	for y, line in enumerate(lines):
		for x, c in enumerate(line):
			m[x, y] = c
		linel = max(linel, len(line))
	del lines

xv, yv = 1, 0
x, y = 0, 0
pc = -1
s = []
mode = "cmd"
r_input = input if sys.version.startswith("3") else raw_input


def escape_0():
	global mode
	s.append(0)
	mode = "str"


def escape_tab():
	global mode
	s.append(9)
	mode = "str"


def escape_lf():
	global mode
	s.append(10)
	mode = "str"


def escape_cr():
	global mode
	s.append(13)
	mode = "str"


def escape_quote():
	global mode
	s.append(34)
	mode = "str"
	
	
def escape_escape():
	global mode
	s.append(92)
	mode = "str"


def _dname((xv, yv)):
	return {
		( 0, -1): "up",
		( 0,  1): "down",
		(-1,  0): "left",
		( 1,  0): "right"
	}.get((xv, yv), None)
	
	
def _debug(i, c, exit=False):
	if DEBUG:
		global pc, mode, x, y, xv, yv, s
		pc += 1
		print(str(pc).zfill(8), end="\t")
		print(mode, (x, y), _dname((xv, yv)), i, hex(id(c)), sep="\t", end="\t")
		print(s)


def str_quote():
	global mode
	mode = "cmd"
		

def str_escape():
	global mode
	mode = "esc"


def push_logical_not():
	a = 0
	if len(s) > 0:
		a = s.pop()
	s.append(1 if a == 0 else 0)


def toggle_str_mode():
	global mode
	mode = "str" if mode == "cmd" else ("cmd" if mode == "str" else mode)


def advance_instr():
	global x, y, xv, yv
	x += xv
	y += yv


def pop_stack_discard():
	if len(s) > 0:
		s.pop()


def push_mod():
	a, b = 0, 0
	if len(s) > 0:
		b = s.pop()
	if len(s) > 0:
		b = s.pop()
	s.append(a % b if b != 0 else 0)


def push_read_integer():
	n = 0
	v = r_input()
	if v.isdigit():
		n = int(v)
	s.append(n)


def push_mul():
	a, b = 0, 0
	if len(s) > 0:
		b = s.pop()
	if len(s) > 0:
		a = s.pop()
	s.append(a * b)


def push_add():
	a, b = 0, 0
	if len(s) > 0:
		b = s.pop()
	if len(s) > 0:
		a = s.pop()
	s.append(a + b)


def pop_write_ascii():
	a = 0
	if len(s) > 0:
		a = s.pop()
	print(chr(a), end='')


def push_sub():
	a, b = 0, 0
	if len(s) > 0:
		b = s.pop()
	if len(s) > 0:
		a = s.pop()
	s.append(a - b)


def pop_write_integer():
	a = 0
	if len(s) > 0:
		a = s.pop()
	print(a, end=' ')


def push_div():
	a, b = 0, 0
	if len(s) > 0:
		b = s.pop()
	if len(s) > 0:
		a = s.pop()
	s.append(a // b if b != 0 else 0)


def dup():
	if len(s) > 0:
		s.append(s[-1])


def go_left():
	global xv, yv
	xv, yv = -1, 0


def go_right():
	global xv, yv
	xv, yv = 1, 0


def go_rand():
	global xv, yv
	t = random.randint(0, 1) * 2 - 1
	xv = random.randint(0, 1)
	yv = (1 ^ xv) * t
	xv *= t


def swp():
	if len(s) > 1:
		s.extend([s.pop(), s.pop()])


def go_up():
	global xv, yv
	xv, yv = 0, -1


def go_x():
	global xv, yv
	xv, yv = 1, 0
	if len(s) > 0 and s.pop() != 0:
		xv = -1


def push_gt():
	a, b = 0, 0
	if len(s) > 0:
		b = s.pop()
	if len(s) > 0:
		a = s.pop()
	s.append(1 if a > b else 0)


def get():
	y, x = -1, -1
	if len(s) > 0:
		y = s.pop()
	if len(s) > 0:
		x = s.pop()
	s.append(ord(m.get((x, y), '\0')))


def put():
	y, x, v = -1, -1, 0
	if len(s) > 0:
		y = s.pop()
	if len(s) > 0:
		x = s.pop()
	if len(s) > 0:
		v = s.pop()
	m[x, y] = chr(v)


def go_down():
	global xv, yv
	xv, yv = 0, 1


def go_y():
	global xv, yv
	xv, yv = 0, 1
	if len(s) > 0 and s.pop() != 0:
		yv = -1


instr = {
	"esc": {
		"0" : escape_0,
		"t" : escape_tab,
		"n" : escape_lf,
		"r" : escape_cr,
		'"' : escape_quote,
		"\\": escape_escape
	},
	"str": {
		"\t": lambda: s.append(9),
		" " : lambda: s.append(32),
		"!" : lambda: s.append(33),
		'"' : str_quote,
		"#" : lambda: s.append(35),
		"$" : lambda: s.append(36),
		"%" : lambda: s.append(37),
		"&" : lambda: s.append(38),
		"'" : lambda: s.append(39),
		"(" : lambda: s.append(40),
		")" : lambda: s.append(41),
		"*" : lambda: s.append(42),
		"+" : lambda: s.append(43),
		"," : lambda: s.append(44),
		"-" : lambda: s.append(45),
		"." : lambda: s.append(46),
		"/" : lambda: s.append(47),
		"0" : lambda: s.append(48),
		"1" : lambda: s.append(49),
		"2" : lambda: s.append(50),
		"3" : lambda: s.append(51),
		"4" : lambda: s.append(52),
		"5" : lambda: s.append(53),
		"6" : lambda: s.append(54),
		"7" : lambda: s.append(55),
		"8" : lambda: s.append(56),
		"9" : lambda: s.append(57),
		":" : lambda: s.append(58),
		";" : lambda: s.append(59),
		"<" : lambda: s.append(60),
		"=" : lambda: s.append(61),
		">" : lambda: s.append(62),
		"?" : lambda: s.append(63),
		"@" : lambda: s.append(64),
		"A" : lambda: s.append(65),
		"B" : lambda: s.append(66),
		"C" : lambda: s.append(67),
		"D" : lambda: s.append(68),
		"E" : lambda: s.append(69),
		"F" : lambda: s.append(70),
		"G" : lambda: s.append(71),
		"H" : lambda: s.append(72),
		"I" : lambda: s.append(73),
		"J" : lambda: s.append(74),
		"K" : lambda: s.append(75),
		"L" : lambda: s.append(76),
		"M" : lambda: s.append(77),
		"N" : lambda: s.append(78),
		"O" : lambda: s.append(79),
		"P" : lambda: s.append(80),
		"Q" : lambda: s.append(81),
		"R" : lambda: s.append(82),
		"S" : lambda: s.append(83),
		"T" : lambda: s.append(84),
		"U" : lambda: s.append(85),
		"V" : lambda: s.append(86),
		"W" : lambda: s.append(87),
		"X" : lambda: s.append(88),
		"Y" : lambda: s.append(89),
		"Z" : lambda: s.append(90),
		"[" : lambda: s.append(91),
		"\\": str_escape,
		"]" : lambda: s.append(93),
		"^" : lambda: s.append(94),
		"_" : lambda: s.append(95),
		"`" : lambda: s.append(96),
		"a" : lambda: s.append(97),
		"b" : lambda: s.append(98),
		"c" : lambda: s.append(99),
		"d" : lambda: s.append(100),
		"e" : lambda: s.append(101),
		"f" : lambda: s.append(102),
		"g" : lambda: s.append(103),
		"h" : lambda: s.append(104),
		"i" : lambda: s.append(105),
		"j" : lambda: s.append(106),
		"k" : lambda: s.append(107),
		"l" : lambda: s.append(108),
		"m" : lambda: s.append(109),
		"n" : lambda: s.append(110),
		"o" : lambda: s.append(111),
		"p" : lambda: s.append(112),
		"q" : lambda: s.append(113),
		"r" : lambda: s.append(114),
		"s" : lambda: s.append(115),
		"t" : lambda: s.append(116),
		"u" : lambda: s.append(117),
		"v" : lambda: s.append(118),
		"w" : lambda: s.append(119),
		"x" : lambda: s.append(120),
		"y" : lambda: s.append(121),
		"z" : lambda: s.append(122),
		"{" : lambda: s.append(123),
		"|" : lambda: s.append(124),
		"}" : lambda: s.append(125),
		"~" : lambda: s.append(126)
	},
	"cmd": {
		"!" : push_logical_not,
		'"' : toggle_str_mode,
		"#" : advance_instr,
		"$" : pop_stack_discard,
		"%" : push_mod,
		"&" : push_read_integer,
		"*" : push_mul,
		"+" : push_add,
		"," : pop_write_ascii,
		"-" : push_sub,
		"." : pop_write_integer,
		"/" : push_div,
		"0" : lambda: s.append(0),
		"1" : lambda: s.append(1),
		"2" : lambda: s.append(2),
		"3" : lambda: s.append(3),
		"4" : lambda: s.append(4),
		"5" : lambda: s.append(5),
		"6" : lambda: s.append(6),
		"7" : lambda: s.append(7),
		"8" : lambda: s.append(8),
		"9" : lambda: s.append(9),
		":" : dup,
		"<" : go_left,
		">" : go_right,
		"?" : go_rand,
		"@" : sys.exit,
		"\\": swp,
		"^" : go_up,
		"_" : go_x,
		"`" : push_gt,
		"g" : get,
		"p" : put,
		"v" : go_down,
		"|" : go_y
	}
}

while True:
	i = m.get((x, y), None)
	if i is not None:
		c = instr[mode].get(i, None)
		if c:
			_debug(i, c)
			c()
	elif x < 0 or y < 0 or y >= nlines or x >= linel:
		_debug(i, c, exit=True)
		sys.exit()
	x += xv
	y += yv
	
