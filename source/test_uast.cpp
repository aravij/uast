#include <catch2/catch.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include "uast.h"

using Catch::Matchers::Equals;
using uast::Node;
using uast::NodeType;

TEST_CASE("Node basic test", "[uast::Node]") {
    SECTION("Constructor") {
        Node node1(NodeType::Expression);
        Node node2(NodeType::ClassDefinition);
        Node node3(NodeType::Expression, node2);  // node1 -> node3 -> node2

        Node node(std::make_shared<Node>(NodeType::ClassDefinition), NodeType::Statement,
                  std::make_shared<Node>(NodeType::Expression));
    }

    std::shared_ptr<Node> parent = std::make_shared<Node>(NodeType::ClassDefinition);
    std::shared_ptr<Node> child = std::make_shared<Node>(NodeType::Expression);
    Node node(parent, NodeType::Statement, child);

    SECTION("Getters") {
        REQUIRE_FALSE(node.IsLeaf());
        REQUIRE(node.GetChildren()[0]->IsLeaf());

        REQUIRE(parent->GetChildren()[0]->GetChildren()[0] == child);
        REQUIRE_THAT(node.GetChildren(), Equals(node.GetChildren()));  // ?

        REQUIRE(node.GetType() == NodeType::Statement);
        REQUIRE(node.GetChildrenCopies(NodeType::FunctionDefinition & NodeType::Expression)[0]
                    .GetType() == NodeType::Expression);
    }

    SECTION("Getters advanced") {
        REQUIRE_THAT(node[NodeType::Statement & NodeType::Expression & NodeType::ClassDefinition],
                     Equals(node.GetChildren()));
    }

    SECTION("Adding children") {
        node.AddChild(parent);
        REQUIRE(node.GetChildren().size() == 2);

        node.AddChildren(node.GetChildrenCopies());
        REQUIRE(node.GetChildren().size() == 4);
    }

    SECTION("Edge cases") {
        REQUIRE_THAT(node[NodeType::ClassDefinition], Equals(std::vector<std::shared_ptr<Node>>()));
    }

    SECTION("Dumping") {
        parent->AddChild(child);
        parent->AddChild(node);
        REQUIRE(parent->ToYAML() ==
                "Node:\n"
                "  Type: ClassDefinition\n"
                "  Children:\n"
                "    - Node:\n"
                "        Type: Statement\n"
                "        Children:\n"
                "          - Node:\n"
                "              Type: Expression\n"
                "              Children: []\n"
                "    - Node:\n"
                "        Type: Expression\n"
                "        Children: []\n"
                "    - Node:\n"
                "        Type: Statement\n"
                "        Children:\n"
                "          - Node:\n"
                "              Type: Expression\n"
                "              Children: []\n");

        std::stringstream s;
        s << node;

        REQUIRE(s.str() ==
                "Node:\n"
                "  Type: Statement\n"
                "  Children:\n"
                "    - Node:\n"
                "        Type: Expression\n"
                "        Children: []\n");
    }
}
