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

TEST_CASE("Node basic test", "[uast::Node]") {
    SECTION("Constructor & Getters") {
        uast::Node node("1");
        uast::Node node_1("12", std::vector<std::string>{"a"}, std::vector<uast::Node>{node});
        uast::Node node_2(
            "22", std::vector<std::string>{"a"},
            std::vector<std::shared_ptr<uast::Node>>{std::make_shared<uast::Node>(node)});
        REQUIRE(node.GetType() == "1");
        REQUIRE(node_1.GetType() == "12");
        REQUIRE(node_2.GetType() == "22");
    }
    std::shared_ptr<uast::Node> node_1 = std::make_shared<uast::Node>("1");
    std::shared_ptr<uast::Node> node_2 = std::make_shared<uast::Node>("2");
    std::shared_ptr<uast::Node> node_p =
        std::make_shared<uast::Node>("+", std::vector<std::string>{"lhs", "rhs"},
                                     std::vector<std::shared_ptr<uast::Node>>{node_1, node_2});
    std::shared_ptr<uast::Node> node_m;

    SECTION("Linking & getter") {
        REQUIRE(node_p->GetChild("lhs") == node_1);
        REQUIRE(node_p->GetChild("rhs") == node_2);

        node_m =
            std::make_shared<uast::Node>("*", std::vector<std::string>{"rhs", "lhs"},
                                         std::vector<std::shared_ptr<uast::Node>>{node_1, node_2});

        REQUIRE(node_m->GetChild("lhs") == node_2);
        REQUIRE(node_m->GetChild("rhs") == node_1);
    }

    SECTION("Adding children") {
        std::shared_ptr<uast::Node> add1 = std::make_shared<uast::Node>("add1");
        std::shared_ptr<uast::Node> add2 = std::make_shared<uast::Node>("add2");
        node_1->AddChild("kek", add1);
        node_1->AddChild("kek2", *add2);
        REQUIRE(node_1->GetChild("kek") == add1);
        REQUIRE(node_1->GetChild("kek2") != add2);
        REQUIRE(node_1->GetChild("kek2")->GetType() == add2->GetType());
        REQUIRE(node_p->GetChild("lhs")->GetChild("kek") == add1);
    }

    std::shared_ptr<uast::Node> add11 = std::make_shared<uast::Node>("add1");
    std::shared_ptr<uast::Node> add12 = std::make_shared<uast::Node>("add2");
    node_1->AddChild("kek", add11);
    node_1->AddChild("kek2", *add12);

    SECTION("Is leaf") {
        REQUIRE(node_p->GetChild("lhs")->GetChild("kek")->IsLeaf());
        REQUIRE(!node_p->GetChild("lhs")->IsLeaf());
        REQUIRE(node_p->GetChild("rhs")->IsLeaf());
    }

    SECTION("Edge cases") {
        REQUIRE(!node_p->GetChild("mhs"));
        REQUIRE_THROWS(
            std::make_shared<uast::Node>("*", std::vector<std::string>{"lhs"},
                                         std::vector<std::shared_ptr<uast::Node>>{node_1, node_2}));
        REQUIRE_THROWS(
            std::make_shared<uast::Node>("*", std::vector<std::string>{"lhs", "rhs"},
                                         std::vector<std::shared_ptr<uast::Node>>{node_1}));
        REQUIRE_THROWS(std::make_shared<uast::Node>("*", std::vector<std::string>{"lhs"},
                                                    std::vector<std::shared_ptr<uast::Node>>{}));
        REQUIRE_NOTHROW(std::make_shared<uast::Node>("*", std::vector<std::string>{},
                                                     std::vector<std::shared_ptr<uast::Node>>{}));
    }
}

TEST_CASE("Node iteration tests") {
    {}
}
