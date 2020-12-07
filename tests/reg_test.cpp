#include <catch2/catch.hpp>
#include "uast.h"

TEST_CASE("Stub test #1") {
    SECTION("UAST stub") {
        REQUIRE(uast::Stub() == "-- Uast loaded successfully");
    }
    SECTION("CPP stub") {
        REQUIRE(uast::cpp_parser::Stub() == "-- Cpp Parser loaded successfully");
    }
}
