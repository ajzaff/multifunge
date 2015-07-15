package com.alanjz.multifunge;

public enum Operator {
  H_BRANCH('_'),
  V_BRANCH('|'),
  INPUT_ASCII('~'),
  OUTPUT_ASCII(','),
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
