#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "cpp_parser.h"

TEST_CASE("Stub test #1") {
    std::cout << "CPP testing" << std::endl;
    std::cout << uast::cpp_parser::Stub() << std::endl;
    REQUIRE(uast::cpp_parser::Stub() == "-- Cpp Parser loaded successfully");
}

TEST_CASE("Stub test #2") {
    { REQUIRE(uast::cpp_parser::Stub() == "-- Cpp Parser loaded successfully"); }
    { REQUIRE(uast::cpp_parser::Stub() == "-- Cpp Parser loaded successfully"); }
}