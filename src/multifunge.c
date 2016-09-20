#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define DEBUG	0
#define INI_LINE_LEN	80
#define INI_BUF_LEN	25
#define INI_STACK_SIZE	11


int NBUFFER = INI_BUF_LEN;
int NLINES = 0;
int *LINEL = NULL;
char **LINES = NULL;
int RUNNING = 1;
int X = 0,
	Y = 0,
	XV = 1,
	YV = 0;
int SS = INI_STACK_SIZE;
int PC = 0;
int SP = 0;
int *S = NULL;
enum mode
{
	MODE_CMD,
	MODE_STR,
	MODE_ESC
} MODE = MODE_CMD;


char *_dirname()
{
	return XV == -1? "left"	:
		XV == 1? "right" :
		YV == -1? "up" : "down";
}


char *_modname()
{
	switch(MODE) {
	case MODE_CMD:
		return "cmd";
	case MODE_STR:
		return "str";
	default:
		return "esc";
	}
}


#if DEBUG
void _debug()
{
	printf("%d\t%s\t(%d,%d)\t%s\t%c\t",
		PC++,
		_modname(),
		X, Y,
		_dirname(),
		LINES[Y][X]);
	int i;
	printf("[");
	for(i=0; i < SP-1; i++)
		printf("%d, ", S[i]);
	printf("%d]\n", S[i]);
}
#endif /* DEBUG */


int push(int v)
{
	S[SP++] = v;
	return 1;
}


int escape(int code)
{
	S[SP++] = code;
	MODE = MODE_STR;
	return 1;
}


int escape_0()
{
	return escape('\0');
}


int escape_tab()
{
	return escape('\t');
}


int escape_lf()
{
	return escape('\n');
}


int escape_cr()
{
	return escape('\r');
}


int escape_quote()
{
	return escape('"');
}


int escape_escape()
{
	return escape('\\');
}


int str_tab()
{
	return push('\t');
}


int str_space()
{
	return push(' ');
}


int str_bang()
{
	return push('!');
}


int str_quote()
{
	MODE = MODE_CMD;
	return 0;
}


int str_hash()
{
	return push('#');
}


int str_dollar()
{
	return push('$');
}


int str_percent()
{
	return push('%');
}


int str_amp()
{
	return push('&');
}


int str_squote()
{
	return push('\'');
}


int str_lparen()
{
	return push('(');
}


int str_rparen()
{
	return push(')');
}


int str_ast()
{
	return push('*');
}


int str_plus()
{
	return push('+');
}


int str_comma()
{
	return push(',');
}


int str_minus()
{
	return push('-');
}


int str_period()
{
	return push('.');
}


int str_slash()
{
	return push('/');
}


int str_0()
{
	return push('0');
}


int str_1()
{
	return push('1');
}


int str_2()
{
	return push('2');
}


int str_3()
{
	return push('3');
}


int str_4()
{
	return push('4');
}


int str_5()
{
	return push('5');
}


int str_6()
{
	return push('6');
}


int str_7()
{
	return push('7');
}


int str_8()
{
	return push('8');
}


int str_9()
{
	return push('9');
}


int str_colon()
{
	return push(':');
}


int str_scolon()
{
	return push(';');
}


int str_lt()
{
	return push('<');
}


int str_eq()
{
	return push('=');
}


int str_gt()
{
	return push('>');
}


int str_query()
{
	return push('?');
}


int str_at()
{
	return push('@');
}


int str_A()
{
	return push('A');
}


int str_B()
{
	return push('B');
}


int str_C()
{
	return push('C');
}


int str_D()
{
	return push('D');
}


int str_E()
{
	return push('E');
}


int str_F()
{
	return push('F');
}


int str_G()
{
	return push('G');
}


int str_H()
{
	return push('H');
}


int str_I()
{
	return push('I');
}


int str_J()
{
	return push('J');
}


int str_K()
{
	return push('K');
}


int str_L()
{
	return push('L');
}


int str_M()
{
	return push('M');
}


int str_N()
{
	return push('N');
}


int str_O()
{
	return push('O');
}


int str_P()
{
	return push('P');
}


int str_Q()
{
	return push('Q');
}


int str_R()
{
	return push('R');
}


int str_S()
{
	return push('S');
}


int str_T()
{
	return push('T');
}


int str_U()
{
	return push('U');
}


int str_V()
{
	return push('V');
}


int str_W()
{
	return push('W');
}


int str_X()
{
	return push('X');
}


int str_Y()
{
	return push('Y');
}


int str_Z()
{
	return push('Z');
}


int str_lbrace() {
	return push('[');
}


int str_escape()
{
	MODE = MODE_ESC;
	return 0;
}


int str_rbrace() {
	return push(']');
}


int str_accent() {
	return push('^');
}


int str_uscore() {
	return push('_');
}


int str_tick() {
	return push('`');
}


int str_a()
{
	return push('a');
}


int str_b()
{
	return push('b');
}


int str_c()
{
	return push('c');
}


int str_d()
{
	return push('d');
}


int str_e()
{
	return push('e');
}


int str_f()
{
	return push('f');
}


int str_g()
{
	return push('g');
}


int str_h()
{
	return push('h');
}


int str_i()
{
	return push('i');
}


int str_j()
{
	return push('j');
}


int str_k()
{
	return push('k');
}


int str_l()
{
	return push('l');
}


int str_m()
{
	return push('m');
}


int str_n()
{
	return push('n');
}


int str_o()
{
	return push('o');
}


int str_p()
{
	return push('p');
}


int str_q()
{
	return push('q');
}


int str_r()
{
	return push('r');
}


int str_s()
{
	return push('s');
}


int str_t()
{
	return push('t');
}


int str_u()
{
	return push('u');
}


int str_v()
{
	return push('v');
}


int str_w()
{
	return push('w');
}


int str_x()
{
	return push('x');
}


int str_y()
{
	return push('y');
}


int str_z()
{
	return push('z');
}


int str_lblock()
{
	return push('{');
}


int str_pipe()
{
	return push('|');
}


int str_rblock()
{
	return push('}');
}


int str_tilde()
{
	return push('~');
}


int push_0()
{
	return push(0);
}


int push_1()
{
	return push(1);
}


int push_2()
{
	return push(2);
}


int push_3()
{
	return push(3);
}


int push_4()
{
	return push(4);
}


int push_5()
{
	return push(5);
}


int push_6()
{
	return push(6);
}


int push_7()
{
	return push(7);
}


int push_8()
{
	return push(8);
}


int push_9()
{
	return push(9);
}


int push_logical_not(void)
{
	S[SP-1] = !S[SP-1];
	return 0;
}


int set_str_mode()
{
	MODE = MODE_STR;
	return 0;
}


int advance_instr()
{
	X += XV;
	Y += YV;
	return 0;
}


int pop_stack_discard()
{
	SP--;
	return 0;
}


int push_mod()
{
	SP--;
	S[SP-1] %= S[SP];
	return 0;
}


int push_read_integer()
{
	int i = 0;
	scanf("%d", &i);
	S[SP++] = i;
	return 1;
}

int push_mul()
{
	SP--;
	S[SP-1] *= S[SP];
	return 0;
}


int push_add()
{
	SP--;
	S[SP-1] += S[SP];
	return 0;
}


int pop_write_ascii()
{
	printf("%c", (char)S[--SP]);
	return 0;
}


int push_sub()
{
	SP--;
	S[SP-1] -= S[SP];
	return 0;
}


int pop_write_integer()
{
	printf("%d ", S[--SP]);
	return 0;
}


int push_div()
{
	SP--;
	S[SP-1] /= S[SP];
	return 0;
}


int dup()
{
	S[SP] = S[SP-1];
	SP++;
	return 1;
}


int go_left()
{
	XV = -1;
	YV = 0;
	return 0;
}


int go_right()
{
	XV = 1;
	YV = 0;
	return 0;
}


int go_away()
{
	// FIXME: optimize this:
	int r = rand() % 4;
	switch (r) {
	case 0:  // up
	case 2:  // down
		XV = 0;
		YV = r - 1;
		return 0;
	case 1:  // left
	default:  // right
		YV = 0;
		XV = r - 2;
		return 0;
	}
}


int stop()
{
	RUNNING = 0;
	return 0;
}


int swp()
{
	int t = S[SP-2];
	S[SP-2] = S[SP-1];
	S[SP-1] = t;
	return 0;
}


int go_up()
{
	XV = 0;
	YV = -1;
	return 0;
}


int go_x()
{
	YV = 0;
	XV = S[--SP]? -1 : 1;
	return 0;
}


int push_gt()
{
	SP--;
	S[SP-1] = S[SP-1] > S[SP];
	return 0;
}


int get()
{
	SP--;
	S[SP-1] = LINES[S[SP]][S[SP-1]];
	return 0;
}


int put()
{
	int y = S[--SP];
	int x = S[--SP];
	int v = S[--SP];
	// FIXME: store out of range in alternate memory:
	LINES[y][x] = (char) v;
	return 0;
}


int go_down()
{
	XV = 0;
	YV = 1;
	return 0;
}


int go_y()
{
	XV = 0;
	YV = S[--SP]? -1 : 1;
	return 0;
}


int (*INSTR[3][128])(void) = {
	{ /* MODE_CMD */
		/* NUL */	NULL,
		/* SOH */	NULL,
		/* STX */	NULL,
		/* ETX */	NULL,
		/* EOT */	NULL,
		/* ENQ */	NULL,
		/* ACK */	NULL,
		/* BEL */	NULL,
		/* BS */	NULL,
		/* HT */	NULL,
		/* LF */	NULL,
		/* VT */	NULL,
		/* FF */	NULL,
		/* CR */	NULL,
		/* SO */	NULL,
		/* SI */	NULL,
		/* DLE */	NULL,
		/* DC1 */	NULL,
		/* DC2 */	NULL,
		/* DC3 */	NULL,
		/* DC4 */	NULL,
		/* NAK */	NULL,
		/* SYN */	NULL,
		/* ETB */	NULL,
		/* CAN */	NULL,
		/* EM */	NULL,
		/* SUB */	NULL,
		/*  ESC */	NULL,
		/*  FS */	NULL,
		/* GS */	NULL,
		/* RS */	NULL,
		/* US */	NULL,
		/* Space */	NULL,
		/* ! */	push_logical_not,
		/* " */	set_str_mode,
		/* # */	advance_instr,
		/* $ */	pop_stack_discard,
		/* % */	push_mod,
		/* & */	push_read_integer,
		/* ' */	NULL,
		/* ( */	NULL,
		/* ) */	NULL,
		/* * */	push_mul,
		/* + */	push_add,
		/* , */	pop_write_ascii,
		/* - */	push_sub,
		/* . */	pop_write_integer,
		/* / */	push_div,
		/* 0 */	push_0,
		/* 1 */	push_1,
		/* 2 */	push_2,
		/* 3 */	push_3,
		/* 4 */	push_4,
		/* 5 */	push_5,
		/* 6 */	push_6,
		/* 7 */	push_7,
		/* 8 */	push_8,
		/* 9 */	push_9,
		/* : */	dup,
		/* ; */	NULL,
		/* < */	go_left,
		/* = */	NULL,
		/* > */	go_right,
		/* ? */	go_away,
		/* @ */	stop,
		/* A */	NULL,
		/* B */	NULL,
		/* C */	NULL,
		/* D */	NULL,
		/* E */	NULL,
		/* F */	NULL,
		/* G */	NULL,
		/* H */	NULL,
		/* I */	NULL,
		/* J */	NULL,
		/* K */	NULL,
		/* L */	NULL,
		/* M */	NULL,
		/* N */	NULL,
		/* O */	NULL,
		/* P */	NULL,
		/* Q */	NULL,
		/* R */	NULL,
		/* S */	NULL,
		/* T */	NULL,
		/* U */	NULL,
		/* V */	NULL,
		/* W */	NULL,
		/* X */	NULL,
		/* Y */	NULL,
		/* Z */	NULL,
		/* [ */	NULL,
		/* \ */	NULL,
		/* ] */	NULL,
		/* ^ */	go_up,
		/* _ */	go_x,
		/* ` */	push_gt,
		/* a */	NULL,
		/* b */	NULL,
		/* c */	NULL,
		/* d */	NULL,
		/* e */	NULL,
		/* f */	NULL,
		/* g */	get,
		/* h */	NULL,
		/* i */	NULL,
		/* j */	NULL,
		/* k */	NULL,
		/* l */	NULL,
		/* m */	NULL,
		/* n */	NULL,
		/* o */	NULL,
		/* p */	put,
		/* q */	NULL,
		/* r */	NULL,
		/* s */	NULL,
		/* t */	NULL,
		/* u */	NULL,
		/* v */	go_down,
		/* w */	NULL,
		/* x */	NULL,
		/* y */	NULL,
		/* z */	NULL,
		/* { */	NULL,
		/* | */	go_y,
		/* } */	NULL,
		/* ~ */	NULL,
		/* DEL */	NULL,
	},
	{ /* MODE_STR */
		/* NUL */	NULL,
		/* SOH */	NULL,
		/* STX */	NULL,
		/* ETX */	NULL,
		/* EOT */	NULL,
		/* ENQ */	NULL,
		/* ACK */	NULL,
		/* BEL */	NULL,
		/* BS */	NULL,
		/* HT */	str_tab,
		/* LF */	NULL,
		/* VT */	NULL,
		/* FF */	NULL,
		/* CR */	NULL,
		/* SO */	NULL,
		/* SI */	NULL,
		/* DLE */	NULL,
		/* DC1 */	NULL,
		/* DC2 */	NULL,
		/* DC3 */	NULL,
		/* DC4 */	NULL,
		/* NAK */	NULL,
		/* SYN */	NULL,
		/* ETB */	NULL,
		/* CAN */	NULL,
		/* EM */	NULL,
		/* SUB */	NULL,
		/*  ESC */	NULL,
		/*  FS */	NULL,
		/* GS */	NULL,
		/* RS */	NULL,
		/* US */	NULL,
		/* Space */	str_space,
		/* ! */	str_bang,
		/* " */	str_quote,
		/* # */	str_hash,
		/* $ */	str_dollar,
		/* % */	str_percent,
		/* & */	str_amp,
		/* ' */	str_squote,
		/* ( */	str_lparen,
		/* ) */	str_rparen,
		/* * */	str_ast,
		/* + */	str_plus,
		/* , */	str_comma,
		/* - */	str_minus,
		/* . */	str_period,
		/* / */	str_slash,
		/* 0 */	str_0,
		/* 1 */	str_1,
		/* 2 */	str_2,
		/* 3 */	str_3,
		/* 4 */	str_4,
		/* 5 */	str_5,
		/* 6 */	str_6,
		/* 7 */	str_7,
		/* 8 */	str_8,
		/* 9 */	str_9,
		/* : */	str_colon,
		/* ; */	str_scolon,
		/* < */	str_lt,
		/* = */ str_eq,
		/* > */	str_gt,
		/* ? */	str_query,
		/* @ */	str_at,
		/* A */	str_A,
		/* B */	str_B,
		/* C */	str_C,
		/* D */	str_D,
		/* E */	str_E,
		/* F */	str_F,
		/* G */	str_G,
		/* H */	str_H,
		/* I */	str_I,
		/* J */	str_J,
		/* K */	str_K,
		/* L */	str_L,
		/* M */	str_M,
		/* N */	str_N,
		/* O */	str_O,
		/* P */	str_P,
		/* Q */	str_Q,
		/* R */	str_R,
		/* S */	str_S,
		/* T */	str_T,
		/* U */	str_U,
		/* V */	str_V,
		/* W */	str_W,
		/* X */	str_X,
		/* Y */	str_Y,
		/* Z */	str_Z,
		/* [ */	str_lbrace,
		/* \ */	str_escape,
		/* ] */	str_rbrace,
		/* ^ */	str_accent,
		/* _ */	str_uscore,
		/* ` */	str_tick,
		/* a */	str_a,
		/* b */	str_b,
		/* c */	str_c,
		/* d */	str_d,
		/* e */	str_e,
		/* f */	str_f,
		/* g */	str_g,
		/* h */	str_h,
		/* i */	str_i,
		/* j */	str_j,
		/* k */	str_k,
		/* l */	str_l,
		/* m */	str_m,
		/* n */	str_n,
		/* o */	str_o,
		/* p */	str_p,
		/* q */	str_q,
		/* r */	str_r,
		/* s */	str_s,
		/* t */	str_t,
		/* u */	str_u,
		/* v */	str_v,
		/* w */	str_w,
		/* x */	str_x,
		/* y */	str_y,
		/* z */	str_z,
		/* { */	str_lblock,
		/* | */	str_pipe,
		/* } */	str_rblock,
		/* ~ */	str_tilde,
		/* DEL */	NULL,
	},
	{ /* MODE_ESC */
		/* NUL */	NULL,
		/* SOH */	NULL,
		/* STX */	NULL,
		/* ETX */	NULL,
		/* EOT */	NULL,
		/* ENQ */	NULL,
		/* ACK */	NULL,
		/* BEL */	NULL,
		/* BS */	NULL,
		/* HT */	NULL,
		/* LF */	NULL,
		/* VT */	NULL,
		/* FF */	NULL,
		/* CR */	NULL,
		/* SO */	NULL,
		/* SI */	NULL,
		/* DLE */	NULL,
		/* DC1 */	NULL,
		/* DC2 */	NULL,
		/* DC3 */	NULL,
		/* DC4 */	NULL,
		/* NAK */	NULL,
		/* SYN */	NULL,
		/* ETB */	NULL,
		/* CAN */	NULL,
		/* EM */	NULL,
		/* SUB */	NULL,
		/*  ESC */	NULL,
		/*  FS */	NULL,
		/* GS */	NULL,
		/* RS */	NULL,
		/* US */	NULL,
		/* Space */	NULL,
		/* ! */	NULL,
		/* " */	escape_quote,
		/* # */	NULL,
		/* $ */	NULL,
		/* % */	NULL,
		/* & */	NULL,
		/* ' */	NULL,
		/* ( */	NULL,
		/* ) */	NULL,
		/* * */	NULL,
		/* + */	NULL,
		/* , */	NULL,
		/* - */	NULL,
		/* . */	NULL,
		/* / */	NULL,
		/* 0 */	escape_0,
		/* 1 */	NULL,
		/* 2 */	NULL,
		/* 3 */	NULL,
		/* 4 */	NULL,
		/* 5 */	NULL,
		/* 6 */	NULL,
		/* 7 */	NULL,
		/* 8 */	NULL,
		/* 9 */	NULL,
		/* : */	NULL,
		/* ; */	NULL,
		/* < */	NULL,
		/* = */	NULL,
		/* > */	NULL,
		/* ? */	NULL,
		/* @ */	NULL,
		/* A */	NULL,
		/* B */	NULL,
		/* C */	NULL,
		/* D */	NULL,
		/* E */	NULL,
		/* F */	NULL,
		/* G */	NULL,
		/* H */	NULL,
		/* I */	NULL,
		/* J */	NULL,
		/* K */	NULL,
		/* L */	NULL,
		/* M */	NULL,
		/* N */	escape_lf,
		/* O */	NULL,
		/* P */	NULL,
		/* Q */	NULL,
		/* R */	escape_cr,
		/* S */	NULL,
		/* T */	escape_tab,
		/* U */	NULL,
		/* V */	NULL,
		/* W */	NULL,
		/* X */	NULL,
		/* Y */	NULL,
		/* Z */	NULL,
		/* [ */	NULL,
		/* \ */	escape_escape,
		/* ] */	NULL,
		/* ^ */	NULL,
		/* _ */	NULL,
		/* ` */	NULL,
		/* a */	NULL,
		/* b */	NULL,
		/* c */	NULL,
		/* d */	NULL,
		/* e */	NULL,
		/* f */	NULL,
		/* g */	NULL,
		/* h */	NULL,
		/* i */	NULL,
		/* j */	NULL,
		/* k */	NULL,
		/* l */	NULL,
		/* m */	NULL,
		/* n */ escape_lf,
		/* o */	NULL,
		/* p */	NULL,
		/* q */	NULL,
		/* r */	escape_cr,
		/* s */	NULL,
		/* t */	escape_tab,
		/* u */	NULL,
		/* v */	NULL,
		/* w */	NULL,
		/* x */	NULL,
		/* y */	NULL,
		/* z */	NULL,
		/* { */	NULL,
		/* | */	NULL,
		/* } */	NULL,
		/* ~ */	NULL,
		/* DEL */	NULL,
	}
};


int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("usage: %s <PROGRAM>\n", argv[0]);
		exit(1);
	}
	FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		printf("error: file is unreadable.\n\n");
		exit(1);
	}
	LINEL = (int*)malloc(sizeof(int) * NBUFFER);
	LINES = (char**)malloc(sizeof(char*) * NBUFFER);
	int i = 0;
	size_t len = 0;
	char *line = NULL;
	while ((i=getline(&line, &len, file)) != -1) {
		if (line[i - 1] == '\n') {  // strip \n, if any.
			line[i - 1] = '\0';
			i--;
		}
		if (NLINES >= NBUFFER) {  // double line memory:
			NBUFFER *= 2;
			LINEL = (int*)realloc(LINEL, sizeof(int) * NBUFFER);
			LINES = (char**)realloc(LINES, sizeof(char*) * NBUFFER);
		}
		LINES[NLINES] = (char*)malloc(i);
		LINES[NLINES] = (char*)memcpy(LINES[NLINES], line, i);
		LINEL[NLINES] = i;
		NLINES++;
	}
	if ((i = NBUFFER - NLINES + 1) > 0) {  // clear remaining line data:
		memset(LINEL+NLINES, 0, i);
		memset(LINES+NLINES, 0, i);
	}
	// Prepare runtime
	S = (int*)malloc(sizeof(int) * SS);
	srand(time(NULL));
	
	while (RUNNING) {
		i = LINES[Y][X];
		if (i) {
			int (*f)(void) = INSTR[MODE][i];
			if (f) {
				#if DEBUG
				_debug();
				#endif /* DEBUG */
				if (f() && SP >= SS) {
					SS *= 2;
					S = (int*)realloc(S, SS);
				}
			}
		}
		X += XV;
		Y += YV;
	}

	// Cleanup
	free(S);
	free(LINEL);
	for (i=0; i < NLINES; i++)
		free(LINES[i]);
	free(LINES);
	fclose(file);
	exit(0);
}
