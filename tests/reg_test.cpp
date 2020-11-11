#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "uast.h"

TEST_CASE("Stub test #1") {
    {
        std::cout << "UAST stub testing:" << std::endl;
        std::cout << uast::Stub() << std::endl;
        REQUIRE(uast::Stub() == "-- Uast loaded successfully");
    }
    {
        std::cout << "PYTHON testing" << std::endl;
        std::cout << uast::python_parser::Stub() << std::endl;
        REQUIRE(uast::python_parser::Stub() == "-- Python Parser loaded successfully");
    }
    {
        std::cout << "CPP testing" << std::endl;
        std::cout << uast::cpp_parser::Stub() << std::endl;
        REQUIRE(uast::cpp_parser::Stub() == "-- Cpp Parser loaded successfully");
    }
    {
        std::cout << "JAVA testing" << std::endl;
        std::cout << uast::java_parser::Stub() << std::endl;
        REQUIRE(uast::java_parser::Stub() == "-- Java Parser loaded successfully");
    }
}