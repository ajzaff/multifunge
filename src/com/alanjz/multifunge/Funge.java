package com.alanjz.multifunge;

public class Funge {
  public Operator operator;
  public Funge[] children;
  public boolean isRoot;
  public Funge(Operator operator) {
    this.operator = operator;
  }

  public void addChild(Direction d, Funge child) {
    if(children == null)
      children = new Funge[4];
    children[d.ordinal()] = child;
  }

  public Funge getChild(Direction d) {
    if(children == null)
      return null;
    return children[d.ordinal()];
  }
}
