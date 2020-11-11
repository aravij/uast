#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "python_parser.h"

TEST_CASE("Stub test #1") {
    std::cout << "PYTHON testing" << std::endl;
    std::cout << uast::python_parser::Stub() << std::endl;
    REQUIRE(uast::python_parser::Stub() == "-- Python Parser loaded successfully");
}

TEST_CASE("Stub test #2") {
    { REQUIRE(uast::python_parser::Stub() == "-- Python Parser loaded successfully"); }
    { REQUIRE(uast::python_parser::Stub() == "-- Python Parser loaded successfully"); }
}