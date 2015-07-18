package com.alanjz.multifunge;

import java.util.Arrays;

public class Caret {

  public Location location;
  public Direction d;

  private Caret(Location location, Direction d) {
    this.location = location;
    this.d = d;
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

  @Override
  public String toString() {
    return String.format("<%s %s>", location, d);
  }

  public static Caret fromOrigin() {
    return new Caret(Location.fromOrigin(), Direction.RIGHT);
  }

  public static Caret from(Location location, Direction d) {
    return new Caret(location, d);
  }
}