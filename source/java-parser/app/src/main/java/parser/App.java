package parser;

import com.github.javaparser.StaticJavaParser;
import com.github.javaparser.ast.CompilationUnit;
import com.github.javaparser.printer.DotPrinter;

import java.io.*;

public class App {
  public static void main(String[] args) throws Exception {
    for (int i = 0; i < args.length; ++i) {
      FileWriter writer;
      try {
        writer = new FileWriter("../uast" + i + ".dot");
      } catch (IOException e) {
          System.err.println("Can't write in file");
          e.printStackTrace();
          throw e;
      }

      try {
        CompilationUnit cu = StaticJavaParser.parse(new FileInputStream(args[i]));
        writer.write(new DotPrinter(true).output(cu) + "\n");
      } catch (Exception e) {
        System.err.println("Problems with parsing " + i + "th file: " + args[i]);
        e.printStackTrace();
        throw e;
      }

      writer.flush();
      writer.close();
      System.out.println("File " + args[i] + " is presented in uast" + i + ".dot");
    }
  }
}
