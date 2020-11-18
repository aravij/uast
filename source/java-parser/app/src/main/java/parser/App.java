package parser;

import parser.SomeClass;
import parser.Analyzer.*;

import java.io.FileNotFoundException;
import java.util.Scanner;

public class App {
  private static final String FILE_PATH = "app/src/main/java/parser/SomeClass.java";
  public static void main(String[] args) throws FileNotFoundException {
    new Analyzer().analyze(FILE_PATH);
  }
}
