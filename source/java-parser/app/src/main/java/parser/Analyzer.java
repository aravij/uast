package parser;

import com.github.javaparser.StaticJavaParser;
import com.github.javaparser.ast.CompilationUnit;
import com.github.javaparser.ast.body.BodyDeclaration;
import com.github.javaparser.ast.body.ClassOrInterfaceDeclaration;
import com.github.javaparser.ast.body.VariableDeclarator;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;

public class Analyzer {
  private static int count = 0;
  FileWriter writer;
  public void analyze(String filePath) throws FileNotFoundException {
    CompilationUnit cu = StaticJavaParser.parse(new FileInputStream(filePath));
    ClassOrInterfaceDeclaration c = cu.getClassByName("SomeClass").get();
    try {
      writer = new FileWriter("graph.dot");
    } catch (Exception e) {
      System.out.println("Something went wrong");
    }
  }

}
