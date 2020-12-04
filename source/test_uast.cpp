#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "uast.h"

TEST_CASE("Stub test #1") {
    std::cout << "UAST stub testing:" << std::endl;
    std::cout << uast::Stub() << std::endl;

    REQUIRE(uast::Stub() == "-- Uast loaded successfully");
}

TEST_CASE("Stub test #2") {
    { REQUIRE(uast::Stub() == "-- Uast loaded successfully"); }
    { REQUIRE(uast::Stub() == "-- Uast loaded successfully"); }
}
