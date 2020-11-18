package parser;

public class SomeClass {
  int a, b;
  private SomeClass(int a) {
    System.out.println("Oh, hello!");
  }
  public SomeClass() {
    System.out.println("I'm here!");
  }
  public void A(String X, double Z) {}
  private String B(int Y) { return ""; }
  protected SomeClass C() { return new SomeClass(); }
  private class YetAnotherClass {}
  public class C1{}
  private class C2{}
}
