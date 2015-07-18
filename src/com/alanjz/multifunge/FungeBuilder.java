package com.alanjz.multifunge;

import java.io.File;
import java.io.IOException;
import java.util.*;

import static com.alanjz.multifunge.Direction.RIGHT;
import static com.alanjz.multifunge.Operator.*;

public class FungeBuilder {
  private List<String> fileLines;
  private FungeBuilder(File file) throws IOException {
    parseLines(new Scanner(file));
  }
  private FungeBuilder(String source) {
    parseLines(new Scanner(source));
  }
  private void parseLines(Scanner scanner) {
    fileLines = new ArrayList<>();
    while(scanner.hasNextLine())
      fileLines.add(scanner.nextLine());
  }
  public Funge compile() {
    Map<Location, FungeEntry> fungeMap;
    Stack<Caret> branchStack;
    FungeEntry rootEntry;
    boolean isRunning;
    Caret caret;

    caret = Caret.fromOrigin();
    fungeMap = new HashMap<>();
    branchStack = new Stack<>();

    // set the root.
    rootEntry = FungeEntry.from(RIGHT, new Funge(R_CARET));
    rootEntry.funge.isRoot = true;
    fungeMap.put(caret.location.copy(), rootEntry);

    isRunning = true;
    FungeEntry prevEntry = rootEntry;
    for( ; isRunning; caret.step()) {
      MapResponse mapResponse;
      FungeEntry currEntry;
      Operator operator;
      Funge funge;

      operator = operatorAt(fungeMap, caret.location);
      mapResponse = handleMap(fungeMap, branchStack, operator, caret);
      if(mapResponse == MapResponse.HALT)
        break;
      switch(mapResponse) {
        case POP:
          caret = branchStack.pop();
          break;
        case PASS:
          currEntry = fungeMap.get(caret.location);
          prevEntry.funge.addChild(caret.d, currEntry.funge);
          prevEntry = currEntry;
          break;
        case CREATE:
          funge = new Funge(operator);
          currEntry = FungeEntry.from(caret.d, funge);
          prevEntry.funge.addChild(caret.d, currEntry.funge);
          fungeMap.put(caret.location.copy(), currEntry);
          prevEntry = currEntry;
          break;

      }

      switch(operator) {
        case HALT:
        case EMPTY:
          isRunning = false;
          break;
        case R_CARET:
        case L_CARET:
        case U_CARET:
        case D_CARET:
          caret.d = operator.caretDirection;
          break;
      }
    }
    return rootEntry.funge;
  }

  public enum MapResponse {
    HALT,
    CREATE,
    POP,
    PASS
  }

  /**
   * Handles a cache hit on the funge map.
   * @return a hit response behavior.
   */
  private MapResponse handleMap(Map<Location, FungeEntry> fungeMap,
                                Stack<Caret> branchStack,
                                Operator operator,
                                Caret caret)
  {
    DirectionMask mappedMask, caretMask;
    FungeEntry mappedEntry;

    mappedEntry = fungeMap.getOrDefault(caret.location, null);
    if(mappedEntry == null) return MapResponse.CREATE;

    mappedMask = mappedEntry.directionMask;
    caretMask = DirectionMask.from(caret.d);

    if(mappedMask.contains(caretMask))
      if(branchStack.empty()) return MapResponse.HALT;
      else { return MapResponse.POP; }

    mappedMask = mappedMask.plus(caretMask);
    fungeMap.put(caret.location, FungeEntry.from(mappedMask, mappedEntry.funge));
    return MapResponse.PASS;
  }

  private Operator operatorAt(Map<Location, FungeEntry> fungeMap, Location location) {
    FungeEntry fungeEntry;
    String line;

    fungeEntry = fungeMap.get(location);
    if(fungeEntry != null)
      return fungeEntry.funge.operator;

    if(location.y >= fileLines.size())
      return EMPTY;

    line = fileLines.get(location.y);
    if(location.x >= line.length())
      return EMPTY;

    return location.equals(-1, 0)?
        Operator.R_CARET :
        searchBy(line.charAt(location.x));
  }

  public static FungeBuilder fromFile(String fileName) throws IOException {
    return new FungeBuilder(new File(fileName));
  }

  public static FungeBuilder fromSource(String source) {
    return new FungeBuilder(source);
  }
}
