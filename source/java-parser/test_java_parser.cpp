#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "java_parser.h"

TEST_CASE( "Stub test #1") {
    std::cout << "JAVA testing" << std::endl;
    std::cout << uast::java_parser::Stub() << std::endl;
    REQUIRE (uast::java_parser::Stub() == "-- Java Parser loaded successfully");
}

TEST_CASE( "Stub test #2") {
    {
        REQUIRE (uast::java_parser::Stub() == "-- Java Parser loaded successfully");
    }
    {
        REQUIRE (uast::java_parser::Stub() == "-- Java Parser loaded successfully");
    }
}