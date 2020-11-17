#define CATCH_CONFIG_MAIN

#include "catch.hpp"
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

TEST_CASE("Node basic test") {
    {
        std::cout << "Test constructors";

        std::shared_ptr<uast::Node> node;
        std::shared_ptr<uast::Node> parent;

        REQUIRE_NOTHROW(node = std::make_shared<uast::Node>(uast::Node()));

        REQUIRE_NOTHROW(parent = node);

        REQUIRE_NOTHROW(node = std::make_shared<uast::Node>(uast::Node(std::vector<std::string>{"kek"},
                                                                       std::vector<std::shared_ptr<uast::Node>>{
                                                                               node})));

        REQUIRE_THROWS(uast::Node(std::vector<std::string>{"kek"}, std::vector<std::shared_ptr<uast::Node>>()));
        REQUIRE_THROWS(uast::Node(std::vector<std::string>(), std::vector<std::shared_ptr<uast::Node>>{node}));
    }

    {
        std::cout << "Test constructors (leaf)";

        REQUIRE_NOTHROW(uast::Leaf<std::string>("kek"));
    }

    {
        std::cout << "Test child adding and getting";

        std::shared_ptr<uast::Node> root = std::make_shared<uast::Node>(uast::Node());
        std::shared_ptr<uast::Node> child1 = std::make_shared<uast::Node>(uast::Node());
        std::shared_ptr<uast::Node> child2 = std::make_shared<uast::Node>(uast::Node());
        std::shared_ptr<uast::Node> child11 = std::make_shared<uast::Node>(uast::Node());

        REQUIRE_NOTHROW(root->AddChild("child1", child1));
        REQUIRE_NOTHROW(root->AddChild("child2", child2));

        REQUIRE_NOTHROW(child1->AddChild("child11", child11));

        REQUIRE(root->GetChild("child1")->GetChild("child11"));
        REQUIRE(root->GetChild("child2")->GetChild("child11") == nullptr);
    }

    {
        std::cout << "Test child adding and getting";

        std::shared_ptr<uast::Node> root = std::make_shared<uast::Node>(uast::Node());
        std::shared_ptr<uast::Node> child1 = std::make_shared<uast::Node>(uast::Node());
        std::shared_ptr<uast::Node> child2 = std::make_shared<uast::Node>(uast::Node());
        std::shared_ptr<uast::Leaf<std::string>> child11 = std::make_shared<uast::Leaf<std::string>>(
                uast::Leaf<std::string>("kek"));

        REQUIRE_NOTHROW(root->AddChild("child1", child1));
        REQUIRE_NOTHROW(root->AddChild("child2", child2));

        REQUIRE(child11);
        REQUIRE_NOTHROW(child1->AddChild("child11", std::dynamic_pointer_cast<uast::Node>(child11)));

        REQUIRE(root->GetChild("child1")->GetChild("child11"));
        REQUIRE(root->GetChild("child2")->GetChild("child11") == nullptr);
    }
}
