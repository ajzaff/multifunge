package com.alanjz.multifunge;

import java.util.Arrays;

public class Location {
  public int x, y;

  public Location(int x, int y) {
    this.x = x;
    this.y = y;
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
    return equals(e.x, e.y);
  }

  public boolean equals(int x, int y) {
    return this.x == x && this.y == y;
  }

  @Override
  public String toString() {
    return String.format("%d %d", x, y);
  }

  public static Location from(int x, int y) {
    return new Location(x, y);
  }

  public static Location fromOrigin() {
    return new Location(-1,0);
  }
}
