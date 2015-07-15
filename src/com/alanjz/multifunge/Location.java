package com.alanjz.multifunge;

import java.util.Arrays;

public class Location {
  public static final Location ORIGIN = new Location(-1, 0);
  public int x, y;

  public Location(int x, int y) {
    this.x = x;
    this.y = y;
  }

  public Location() {
    this(0,0);
  }

  public void add(Direction d) {
    x += d.dx;
    y += d.dy;
  }

  public Location copy() {
    return new Location(x,y);
  }

  @Override
  public int hashCode() {
    return Arrays.hashCode(new int[] { x, y });
  }

  @Override
  public boolean equals(Object o) {
    if(!(o instanceof Location))
      return false;
    Location e = (Location) o;
    return x == e.x && y == e.y;
  }
}
