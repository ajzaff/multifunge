package com.alanjz.multifunge;

import java.util.Arrays;

public enum Direction {
  RIGHT(1,0),
  DOWN(0,1),
  UP(0,-1),
  LEFT(-1,0);

  public final int dx, dy;
  public final int mask;

  Direction(int dx, int dy) {
    this.dx = dx;
    this.dy = dy;
    this.mask = 1 << ordinal();
  }
}
