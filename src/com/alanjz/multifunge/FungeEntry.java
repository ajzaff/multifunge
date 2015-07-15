package com.alanjz.multifunge;

public class FungeEntry {
  public DirectionMask directionMask;
  public final Funge funge;
  private FungeEntry(DirectionMask directionMask, Funge funge) {
    this.directionMask = directionMask;
    this.funge = funge;
  }
  public static FungeEntry from(DirectionMask directionMask, Funge funge) {
    return new FungeEntry(directionMask, funge);
  }
  public static FungeEntry from(Direction direction, Funge funge) {
    return new FungeEntry(DirectionMask.from(direction), funge);
  }
}
