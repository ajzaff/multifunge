package com.alanjz.multifunge;

public enum Operator {
  FORK('*'),
  SSL_MODE('r'),
  FUNCTION_MODE('f'),
  ADD('+'),
  SUB('-'),
  DIV('/'),
  MUL('x'),
  MOD('%'),
  NOT('!'),
  JUMP_TO(';'),
  JUMP_1('#'),
  PUT('p'),
  GET('g'),
  PAR_MUTEX('S'),
  PAR_SEMAPHORE('s'),
  STRING_MODE_NATIVE('\''),
  STRING_MODE_FIFO('`'),
  STRING_MODE_FILO('"'),
  H_BRANCH('_'),
  V_BRANCH('|'),
  PUSH_INTEGER('&'),
  PUSH_NINE('9'),
  PUSH_EIGHT('8'),
  PUSH_SEVEN('7'),
  PUSH_SIX('6'),
  PUSH_FIVE('5'),
  PUSH_FOUR('4'),
  PUSH_THREE('3'),
  PUSH_TWO('2'),
  PUSH_ONE('1'),
  PUSH_ZERO('0'),
  PUSH_TOP(':'),
  PUSH_ASCII('~'),
  POP_ASCII(','),
  POP('$'),
  ND_CARET('?'),
  R_CARET('>',Direction.RIGHT),
  D_CARET('v',Direction.DOWN),
  U_CARET('^',Direction.UP),
  L_CARET('<',Direction.LEFT),
  HALT('@'),
  NOP(' '),
  EMPTY('\u0000');

  private final char glyph;
  public Direction caretDirection;

  Operator(char glyph) {
    this(glyph, null);
  }

  Operator(char glyph, Direction caretDirection) {
    this.caretDirection = caretDirection;
    this.glyph = glyph;
  }

  public static Operator searchBy(char glyph) {
    for(Operator op : Operator.values()) {
      if(op.glyph == glyph) {
        return op;
      }
    }
    return NOP;
  }
}
