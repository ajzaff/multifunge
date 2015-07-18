package com.alanjz.multifunge;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.EmptyStackException;
import java.util.Stack;

public class FungeRunner implements Runnable {
  public static final boolean DEBUG = true;
  private static BufferedReader stdioReader;
  private Funge funge;
  private Thread th;
  private Logger logger;
  public FungeRunner(Funge funge) {
    this.funge = funge;
    this.logger = new Logger();
    th = new Thread(this);
  }
  public void start() {
    th.start();
  }
  @Override
  public void run() {
    Stack<Integer> dataStack;
    boolean isRunning;
    Caret caret;
    Funge cur;

    dataStack = new Stack<>();
    caret = Caret.fromOrigin();
    isRunning = true;
    cur = funge;
    while(isRunning) {
      if(cur == null) continue;
      Operator o = cur.operator;
      switch (o) {
        case R_CARET:
        case L_CARET:
        case U_CARET:
        case D_CARET:
          caret.d = o.caretDirection;
          break;
        case PUSH_ASCII:
          pushChar(dataStack);
          break;
        case POP_ASCII:
          char chr = popChar(dataStack);
          if(chr != 0)
            System.out.print(chr);
          break;
        case HALT:
          isRunning = false;
          break;
      }
      if(isRunning) {
        cur = cur.getChild(caret.d);
        if(cur == null)
          getLogger().error(
              "detected diverging code path during execution of program;",
              "caret vector increases indefinitely;",
              String.format("at: %s.", caret)
          );
      }
    }
  }

  private void pushChar(Stack<Integer> dataStack) {
    try {
      if(stdioReader == null)
        stdioReader = new BufferedReader(
            new InputStreamReader(System.in));
      dataStack.push(stdioReader.read());
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

  private Logger getLogger() {
    return logger;
  }
}
