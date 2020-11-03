#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE( "Testing tests #1") {
    std::cout << "CPP testing\n";
    std::vector<int> v;
    REQUIRE (v.empty());
}

TEST_CASE( "Testing tests #2" ) {
    int b = 4;
    REQUIRE (b != 5);
}