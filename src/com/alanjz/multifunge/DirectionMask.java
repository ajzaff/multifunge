package com.alanjz.multifunge;

public class DirectionMask {
  public static final DirectionMask EMPTY = new DirectionMask(0);
  private final int mask;
  private DirectionMask(int mask, Direction... directions) {
    for(Direction d : directions) {
      mask |= d.mask;
    }
    this.mask = mask;
  }
  public boolean contains(int mask) {
    return (this.mask & mask) != 0;
  }
  public boolean contains(Direction direction) {
    return contains(direction.mask);
  }
  public boolean contains(DirectionMask directionMask) {
    return contains(directionMask.mask);
  }
  public DirectionMask plus(int mask) {
    if(contains(mask))
      return this;
    return new DirectionMask(this.mask | mask);
  }
  public DirectionMask plus(Direction direction) {
    return plus(direction.mask);
  }
  public DirectionMask plus(DirectionMask directionMask) {
    return plus(directionMask.mask);
  }
  public static DirectionMask from(DirectionMask mask, Direction... directions) {
    return new DirectionMask(mask.mask, directions);
  }
  public static DirectionMask from(Direction... directions) {
    return new DirectionMask(0, directions);
  }
  public static DirectionMask from(Direction direction) {
    return new DirectionMask(direction.mask);
  }
}
