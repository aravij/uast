#include <catch2/catch.hpp>
#include "cpp_parser.h"

TEST_CASE("Stub test #1") {
    SECTION("CPP testing") {
        REQUIRE(uast::cpp_parser::Stub() == "-- Cpp Parser loaded successfully");
    }
}

TEST_CASE("Stub test #2") {
    SECTION("More CPP testing") {
        REQUIRE(uast::cpp_parser::Stub() == "-- Cpp Parser loaded successfully");
    }

    SECTION("More CPP testing") {
        REQUIRE(uast::cpp_parser::Stub() == "-- Cpp Parser loaded successfully");
    }
}
