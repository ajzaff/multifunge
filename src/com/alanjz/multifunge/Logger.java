package com.alanjz.multifunge;

import java.io.PrintStream;

public class Logger {
  public void error(String title, String... messages) {
    System.err.println(String.format("error   %s", title));
    log(System.err, messages);
  }
  public void warn(String title, String... messages) {
    System.out.println(String.format("warn    %s", title));
    log(System.out, messages);
  }
  public void info(String title, String... messages) {
    System.out.println(String.format("info    %s", title));
    log(System.out, messages);
  }
  private void log(PrintStream printStream, String... messages) {
    for(String s : messages) {
      printStream.println(String.format("        %s", s));
    }
  }
}
