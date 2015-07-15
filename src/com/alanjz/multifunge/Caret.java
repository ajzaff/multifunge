package com.alanjz.multifunge;

import java.util.Arrays;

public class Caret {
  public static final Caret ORIGIN = new Caret(Location.ORIGIN, Direction.RIGHT);

  public Location location;
  public Direction d;

  public Caret(Location location, Direction d) {
    this.location = location;
    this.d = d;
  }

  public Caret() {
    this(new Location(), Direction.RIGHT);
  }

  public void step() {
    location.add(d);
  }

  public Caret copy() {
    return new Caret(location.copy(), d);
  }

  @Override
  public int hashCode() {
    return Arrays.hashCode(new Object[]{location, d});
  }

  @Override
  public boolean equals(Object o) {
    if(!(o instanceof Caret))
      return false;
    Caret e = (Caret) o;
    return location.equals(e.location) && d == e.d;
  }
}
