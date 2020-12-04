#include <iostream>
#include "uast.h"

int main() {
    std::cout << "Empty test started:" << std::endl;
    std::cout << "- Testing uast:" << std::endl;
    std::cout << uast::Stub() << std::endl;
    std::cout << "- Testing cpp-parser:" << std::endl;
    std::cout << uast::cpp_parser::Stub() << std::endl;

    return 0;
}
