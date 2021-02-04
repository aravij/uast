#include <catch2/catch.hpp>
#include "uast.h"

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

TEST_CASE("Node iteration tests", "[uast::Node::DFSIterator]") {
    std::shared_ptr<uast::Node> node_1 = std::make_shared<uast::Node>("1");
    std::shared_ptr<uast::Node> node_2 = std::make_shared<uast::Node>("2");
    std::shared_ptr<uast::Node> node_3 = std::make_shared<uast::Node>("3");
    std::shared_ptr<uast::Node> node_4 = std::make_shared<uast::Node>("4");
    std::shared_ptr<uast::Node> node_5 = std::make_shared<uast::Node>("5");

    node_1->AddChild("2", node_2);
    node_1->AddChild("4", node_4);
    node_4->AddChild("3", node_3);
    node_3->AddChild("5", node_5);

    /*
     *  1
     * | \
     * 2  4
     *    |
     *    3
     *    |
     *    6
     */

    SECTION("Iterators comparison") {
        REQUIRE(node_1->DFS().begin() != node_1->DFS().end());
        REQUIRE(node_1->DFS().end() == node_1->DFS().end());
        REQUIRE(node_1->DFS().begin() == node_1->DFS().begin());
        REQUIRE(node_2->DFS().end() == node_2->DFS().end());
    }

    SECTION("Iterators usage in for") {
        bool one, two, three, four, five;
        one = two = three = four = five = false;

        for (auto pair : node_1->DFS()) {
            if (pair.first == "1") {
                one = true;
            }
            if (pair.first == "2") {
                two = true;
            }
            if (pair.first == "3") {
                three = true;
            }
            if (pair.first == "4") {
                four = true;
            }
            if (pair.first == "5") {
                five = true;
            }
        }

        REQUIRE(!one);
        REQUIRE(two);
        REQUIRE(three);
        REQUIRE(four);
        REQUIRE(five);
    }
}
