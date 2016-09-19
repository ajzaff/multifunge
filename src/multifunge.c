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
	XV = 0,
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


inline char *_dirname()
{
	return XV == -1? "left"	:
		XV == 1? "right" :
		YV == -1? "up" : "down";
}


inline char *_modname()
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


inline int getl(int x, int y)
{
	if (y >= 0 && y < NLINES && x >= 0 && x < LINEL[y])
		return LINES[y][x];
	return 0;
}


inline int geti()
{
	return getl(X, Y);
}


inline void _debug()
{
	printf("%d\t%s\t(%d,%d)\t%s\t%c\t%d\n",
		PC,
		_modname(),
		X, Y,
		_dirname(),
		geti(),
		SP);
}


inline int push(int v)
{
	S[SP++] = v;
	return 1;
}


inline int escape(int code)
{
	S[SP++] = code;
	MODE = MODE_STR;
	return 1;
}


inline int escape_0()
{
	return escape(0);
}


inline int escape_tab()
{
	return escape(9);
}


inline int escape_lf()
{
	return escape(10);
}


inline int escape_cr()
{
	return escape(13);
}


inline int escape_quote()
{
	return escape(34);
}


inline int escape_escape()
{
	return escape(92);
}


inline int str_quote()
{
	MODE = MODE_CMD;
	return 0;
}


inline int str_escape()
{
	MODE = MODE_ESC;
	return 0;
}


inline int push_logical_not()
{
	S[SP-1] = !S[SP-1];
	return 0;
}


inline int toggle_str_mode()
{
	MODE = MODE == MODE_CMD?
		MODE_STR : MODE_CMD;
	return 0;
}


inline int advance_instr()
{
	X += XV;
	Y += YV;
	return 0;
}


inline int pop_stack_discard()
{
	SP--;
	return 0;
}


inline int push_mod()
{
	SP--;
	S[SP-1] %= S[SP];
	return 0;
}


inline int push_read_integer()
{
	int i = 0;
	scanf("%d", &i);
	S[SP++] = i;
	return 1;
}

inline int push_mul()
{
	SP--;
	S[SP-1] *= S[SP];
	return 0;
}


inline int push_add()
{
	SP--;
	S[SP-1] += S[SP];
	return 0;
}


inline int pop_write_ascii()
{
	printf("%c", (char)S[--SP]);
	return 0;
}


inline int push_sub()
{
	SP--;
	S[SP-1] -= S[SP];
	return 0;
}


inline int pop_write_integer()
{
	printf("%d ", S[--SP]);
	return 0;
}


inline int push_div()
{
	SP--;
	S[SP-1] /= S[SP];
	return 0;
}


inline int dup()
{
	S[SP] = S[SP-1];
	SP++;
	return 1;
}


inline int go_left()
{
	XV = -1;
	YV = 0;
	return 0;
}


inline int go_right()
{
	XV = 1;
	YV = 0;
	return 0;
}


inline int go_away()
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


inline int stop()
{
	RUNNING = 0;
	return 0;
}


inline int swp()
{
	int t = S[SP-2];
	S[SP-2] = S[SP-1];
	S[SP-1] = t;
	return 0;
}


inline int go_up()
{
	XV = 0;
	YV = -1;
	return 0;
}


inline int go_x()
{
	YV = 0;
	XV = S[SP--]? -1 : 1;
	return 0;
}


inline int push_gt()
{
	SP--;
	S[SP-1] = S[SP-1] > S[SP];
	return 0;
}


inline int get()
{
	SP--;
	S[SP-1] = getl(S[SP-1], S[SP]);
	return 0;
}


inline int put()
{
	int y = S[--SP];
	int x = S[--SP];
	int v = S[--SP];
	// FIXME: store out of range in alternate memory:
	if (y >= 0 && y < NLINES && x >= 0 && x < LINEL[y])
		LINES[y][x] = (char) v;
	return 0;
}


inline int go_down()
{
	XV = 0;
	YV = 1;
	return 0;
}


inline int go_y()
{
	XV = 0;
	YV = S[SP--]? -1 : 1;
	return 0;
}


const int (*INSTR[3][128])(void) = {
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
		/* ! */	NULL,
		/* " */	NULL,
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
		/* 0 */	NULL,
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
		/* n */	NULL,
		/* o */	NULL,
		/* p */	NULL,
		/* q */	NULL,
		/* r */	NULL,
		/* s */	NULL,
		/* t */	NULL,
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
		/* " */	NULL,
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
		/* 0 */	NULL,
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
		/* n */	NULL,
		/* o */	NULL,
		/* p */	NULL,
		/* q */	NULL,
		/* r */	NULL,
		/* s */	NULL,
		/* t */	NULL,
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
		/* " */	NULL,
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
		/* 0 */	NULL,
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
		/* n */	NULL,
		/* o */	NULL,
		/* p */	NULL,
		/* q */	NULL,
		/* r */	NULL,
		/* s */	NULL,
		/* t */	NULL,
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
		// FIXME: implement main interpreter loop
		break;
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
