#pragma once

#include <memory>
#include <iterator>
#include <unordered_map>
#include <any>
#include <vector>
#include <sstream>
#include <iostream>
#include <stack>
#include <functional>
#include "node_type.h"

namespace uast {
    class Node {
        std::vector<std::shared_ptr<Node>> children_;
        NodeType type_;

        void ToYAMLIndented(std::stringstream &stream, int indent = 0);

    public:
        Node(std::shared_ptr<Node> parent, NodeType type, std::shared_ptr<Node> child);

        Node(std::shared_ptr<Node> parent, NodeType type, std::vector<std::shared_ptr<Node>> children);

        Node(NodeType type, std::shared_ptr<Node> child);

        Node(NodeType type, std::vector<std::shared_ptr<Node>> children);

        Node(std::shared_ptr<Node> parent, NodeType type);

        Node(NodeType type, Node child_to_copy);

        Node(NodeType type, std::vector<Node> children_to_copy);

        Node(NodeType type);

        void AddChild(std::shared_ptr<Node> child);

        void AddChild(Node child_to_copy);

        void AddChildren(std::vector<std::shared_ptr<Node>> children);

        void AddChildren(std::vector<Node> children_to_copy);

        std::vector<std::shared_ptr<Node>> GetChildren(NodeType node_type);

        std::vector<std::shared_ptr<Node>> GetChildren(std::vector<NodeType> node_types);

        std::vector<Node> GetChildrenCopies(NodeType node_type);

        std::vector<Node> GetChildrenCopies(std::vector<NodeType> node_types);

        std::vector<std::shared_ptr<Node>> GetChildren();

        std::vector<Node> GetChildrenCopies();

        NodeType GetType();

        bool IsLeaf();

        std::vector<std::shared_ptr<Node>> operator[](NodeType node_type);

        std::vector<std::shared_ptr<Node>> operator[](std::vector<NodeType> node_types);

        std::vector<std::shared_ptr<Node>> operator[](bool);

        std::string ToYAML();
    };

    inline std::ostream &operator<<(std::ostream &out, Node &node) {
        out << node.ToYAML();

        return out;
    }
}
