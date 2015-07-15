package com.alanjz.multifunge;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.EmptyStackException;
import java.util.Scanner;
import java.util.Stack;

import static com.alanjz.multifunge.Operator.*;

public class FungeRunner implements Runnable {
  private Funge funge;
  private Thread th;
  public FungeRunner(Funge funge) {
    this.funge = funge;
    th = new Thread(this);
  }
  public void start() {
    th.start();
  }
  @Override
  public void run() {
    Stack<Integer> dataStack;
    BufferedReader bufferedReader;
    Caret caret;
    Funge cur;

    dataStack = new Stack<>();
    bufferedReader = new BufferedReader(new InputStreamReader(System.in));
    caret = new Caret();
    cur = funge;
    while(cur != null) {
      Operator o = cur.operator;
      switch (o) {
        case R_CARET:
        case L_CARET:
        case U_CARET:
        case D_CARET:
          caret.d = o.caretDirection;
          break;
        case INPUT_ASCII:
          pushChar(dataStack, bufferedReader);
          break;
        case OUTPUT_ASCII:
          char chr = popChar(dataStack);
          if(chr != 0)
            System.out.print(chr);
          break;
      }
      cur = cur.getChild(caret.d);
    }
  }

  private void pushChar(Stack<Integer> dataStack, BufferedReader bufferedReader) {
    try {
      dataStack.push(bufferedReader.read());
    }
    catch (IOException e) {
      dataStack.push(0);
    }
  }

  private char popChar(Stack<Integer> dataStack) {
    try {
      return (char) (int) dataStack.pop();
    }
    catch (EmptyStackException e) {
      return 0;
    }
  }
}
