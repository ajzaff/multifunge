from __future__ import print_function
import sys


if len(sys.argv) < 2:
	print("usage: %s <PROGRAM>" % sys.argv[0])
	sys.exit(1)

m = {}
with open(sys.argv[1], "rb") as f:
	global lines
	lines = [list(line) for line in f.readlines()]
	nlines = len(lines)

xv, yv = 1, 0
x, y = 0, 0
pc = -1
sp = 0
s = [0 for _ in range(256)]
mode = "cmd"
r_input = input if sys.version.startswith("3") else raw_input


def _pop():
	global sp
	if sp > 0:
		sp -= 1
		return s[sp]
	return 0


def _push(v):
	global sp
	if sp < len(s):
		s[sp] = v
	else:
		s.append(v)
	sp += 1
	

def _get():
	try:
		return lines[y][x]
	except:
		return m.get((x, y), None)


def escape_0():
	global mode
	_push(0)
	mode = "str"


def escape_tab():
	global mode
	_push(9)
	mode = "str"


def escape_lf():
	global mode
	_push(10)
	mode = "str"


def escape_cr():
	global mode
	_push(13)
	mode = "str"


def escape_quote():
	global mode
	_push(34)
	mode = "str"
	
	
def escape_escape():
	global mode
	_push(92)
	mode = "str"


def _dname((xv, yv)):
	return {
		( 0, -1): "up",
		( 0,  1): "down",
		(-1,  0): "left",
		( 1,  0): "right"
	}.get((xv, yv), None)
	
	
def _debug(i, c, exit=False):
	global pc, mode, x, y, xv, yv, s
	pc += 1
	print(str(pc).zfill(8), end="\t")
	print(mode, (x, y), _dname((xv, yv)), i, hex(id(c)), sep="\t", end="\t")
	print(s[:sp])


def str_quote():
	global mode
	mode = "cmd"
		

def str_escape():
	global mode
	mode = "esc"


def push_logical_not():
	a = 0
	if sp >= 0:
		a = _pop()
	_push(1 if a == 0 else 0)


def toggle_str_mode():
	global mode
	mode = "str" if mode == "cmd" else ("cmd" if mode == "str" else mode)


def advance_instr():
	global x, y, xv, yv
	x += xv
	y += yv


def pop_stack_discard():
	if sp >= 0:
		_pop()


def push_mod():
	if sp > 1:
		global sp
		s[sp-2] = s[sp-2] % s[sp-1]
		sp -= 1


def push_read_integer():
	global sp
	s[sp] = int(r_input())
	sp += 1


def push_mul():
	if sp > 1:
		global sp
		s[sp-2] = s[sp-2] * s[sp-1]
		sp -= 1


def push_add():
	if sp > 1:
		global sp
		s[sp-2] = s[sp-2] + s[sp-1]
		sp -= 1


def pop_write_ascii():
	if sp > 0:
		global sp
		print(chr(s[sp-1]), end='')
		sp -= 1


def push_sub():
	if sp > 1:
		global sp
		s[sp-2] = s[sp-2] - s[sp-1]
		sp -= 1


def pop_write_integer():
	a = 0
	if sp >= 0:
		a = _pop()
	print(a, end=' ')


def push_div():
	a, b = 0, 0
	if sp >= 0:
		b = _pop()
	if sp >= 0:
		a = _pop()
	_push(a // b if b != 0 else 0)


def dup():
	if sp > 0:
		_push(s[sp-1])


def go_left():
	global xv, yv
	xv, yv = -1, 0


def go_right():
	global xv, yv
	xv, yv = 1, 0


def go_away():
	global xv, yv
	import random
	t = random.randint(0, 1) * 2 - 1
	xv = random.randint(0, 1)
	yv = (1 ^ xv) * t
	xv *= t


def swp():
	if len(s) > 1:
		s.extend([_pop(), _pop()])


def go_up():
	global xv, yv
	xv, yv = 0, -1


def go_x():
	global xv, yv
	xv, yv = 1, 0
	if sp >= 0 and _pop() != 0:
		xv = -1


def push_gt():
	a, b = 0, 0
	if sp >= 0:
		b = _pop()
	if sp >= 0:
		a = _pop()
	_push(1 if a > b else 0)


def get():
	y, x = -1, -1
	if sp >= 0:
		y = _pop()
	if sp >= 0:
		x = _pop()
	if 0 <= y < nlines and 0 <= x < len(lines[y]):
		_push(ord(lines[y][x]))
		return
	_push(ord(m.get((x, y), '\0')))


def put():
	y, x, v = -1, -1, 0
	if sp >= 0:
		y = _pop()
	if sp >= 0:
		x = _pop()
	if sp >= 0:
		v = _pop()
	if 0 <= y < nlines and 0 <= x < len(lines[y]):
		lines[y][x] = chr(v)
		return
	m[x, y] = chr(v)


def go_down():
	global xv, yv
	xv, yv = 0, 1


def go_y():
	global xv, yv
	xv, yv = 0, 1
	if sp >= 0 and _pop() != 0:
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
		"\t": lambda: _push(9),
		" " : lambda: _push(32),
		"!" : lambda: _push(33),
		'"' : str_quote,
		"#" : lambda: _push(35),
		"$" : lambda: _push(36),
		"%" : lambda: _push(37),
		"&" : lambda: _push(38),
		"'" : lambda: _push(39),
		"(" : lambda: _push(40),
		")" : lambda: _push(41),
		"*" : lambda: _push(42),
		"+" : lambda: _push(43),
		"," : lambda: _push(44),
		"-" : lambda: _push(45),
		"." : lambda: _push(46),
		"/" : lambda: _push(47),
		"0" : lambda: _push(48),
		"1" : lambda: _push(49),
		"2" : lambda: _push(50),
		"3" : lambda: _push(51),
		"4" : lambda: _push(52),
		"5" : lambda: _push(53),
		"6" : lambda: _push(54),
		"7" : lambda: _push(55),
		"8" : lambda: _push(56),
		"9" : lambda: _push(57),
		":" : lambda: _push(58),
		";" : lambda: _push(59),
		"<" : lambda: _push(60),
		"=" : lambda: _push(61),
		">" : lambda: _push(62),
		"?" : lambda: _push(63),
		"@" : lambda: _push(64),
		"A" : lambda: _push(65),
		"B" : lambda: _push(66),
		"C" : lambda: _push(67),
		"D" : lambda: _push(68),
		"E" : lambda: _push(69),
		"F" : lambda: _push(70),
		"G" : lambda: _push(71),
		"H" : lambda: _push(72),
		"I" : lambda: _push(73),
		"J" : lambda: _push(74),
		"K" : lambda: _push(75),
		"L" : lambda: _push(76),
		"M" : lambda: _push(77),
		"N" : lambda: _push(78),
		"O" : lambda: _push(79),
		"P" : lambda: _push(80),
		"Q" : lambda: _push(81),
		"R" : lambda: _push(82),
		"S" : lambda: _push(83),
		"T" : lambda: _push(84),
		"U" : lambda: _push(85),
		"V" : lambda: _push(86),
		"W" : lambda: _push(87),
		"X" : lambda: _push(88),
		"Y" : lambda: _push(89),
		"Z" : lambda: _push(90),
		"[" : lambda: _push(91),
		"\\": str_escape,
		"]" : lambda: _push(93),
		"^" : lambda: _push(94),
		"_" : lambda: _push(95),
		"`" : lambda: _push(96),
		"a" : lambda: _push(97),
		"b" : lambda: _push(98),
		"c" : lambda: _push(99),
		"d" : lambda: _push(100),
		"e" : lambda: _push(101),
		"f" : lambda: _push(102),
		"g" : lambda: _push(103),
		"h" : lambda: _push(104),
		"i" : lambda: _push(105),
		"j" : lambda: _push(106),
		"k" : lambda: _push(107),
		"l" : lambda: _push(108),
		"m" : lambda: _push(109),
		"n" : lambda: _push(110),
		"o" : lambda: _push(111),
		"p" : lambda: _push(112),
		"q" : lambda: _push(113),
		"r" : lambda: _push(114),
		"s" : lambda: _push(115),
		"t" : lambda: _push(116),
		"u" : lambda: _push(117),
		"v" : lambda: _push(118),
		"w" : lambda: _push(119),
		"x" : lambda: _push(120),
		"y" : lambda: _push(121),
		"z" : lambda: _push(122),
		"{" : lambda: _push(123),
		"|" : lambda: _push(124),
		"}" : lambda: _push(125),
		"~" : lambda: _push(126)
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
		"0" : lambda: _push(0),
		"1" : lambda: _push(1),
		"2" : lambda: _push(2),
		"3" : lambda: _push(3),
		"4" : lambda: _push(4),
		"5" : lambda: _push(5),
		"6" : lambda: _push(6),
		"7" : lambda: _push(7),
		"8" : lambda: _push(8),
		"9" : lambda: _push(9),
		":" : dup,
		"<" : go_left,
		">" : go_right,
		"?" : go_away,
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
	i = _get()
	if i is not None:
		c = instr[mode].get(i, None)
		if c is not None:
			if __debug__:
				_debug(i, c)
			c()
	x += xv
	y += yv
	
