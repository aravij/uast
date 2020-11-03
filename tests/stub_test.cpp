#include <iostream>
#include "uast.h"
#include "cpp_parser.h"
#include "java_parser.h"
#include "python_parser.h"

int main() {
    std::cout << "Empty test started:" << std::endl;
    std::cout << "- Testing uast:" << std::endl;
    std::cout << uast::Stub() << std::endl;
    std::cout << "- Testing cpp-parser:" << std::endl;
    std::cout << uast::cpp_parser::Stub() << std::endl;
    std::cout << "- Testing java-parser:" << std::endl;
    std::cout << uast::java_parser::Stub() << std::endl;
    std::cout << "- Testing python-parser:" << std::endl;
    std::cout << uast::python_parser::Stub() << std::endl;


    return 0;
}