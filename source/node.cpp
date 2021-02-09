#include "node.h"

using NodePtr = std::shared_ptr<uast::Node>;

namespace uast {
    Node::Node(NodePtr parent, NodeType type, NodePtr child) : type_(type) {
        AddChild(child);
        parent->AddChild(*this);
    }

    Node::Node(NodeType type, NodePtr child) : type_(type) {
        AddChild(child);
    }

    Node::Node(NodePtr parent, NodeType type) : type_(type) {
        parent->AddChild(*this);
    }

    Node::Node(NodeType type, Node child_to_copy) : type_(type) {
        AddChild(child_to_copy);
    }

    Node::Node(NodeType type, std::vector<std::shared_ptr<Node>> children) : type_(type) {
        AddChildren(children);
    }

    Node::Node(NodeType type, std::vector<Node> children_to_copy) : type_(type) {
        AddChildren(children_to_copy);
    }

    Node::Node(std::shared_ptr<Node> parent, NodeType type, std::vector<std::shared_ptr<Node>> children) : type_(type) {
        AddChildren(children);
        parent->AddChild(*this);
    }

    Node::Node(NodeType type) : type_(type) {

    }

    void Node::AddChild(NodePtr child) {
        children_.push_back(child);
    }

    void Node::AddChild(Node child_to_copy) {
        children_.push_back(std::make_shared<Node>(child_to_copy));
    }

    void Node::AddChildren(std::vector<NodePtr> children) {
        for (auto child : children) {
            AddChild(child);
        }
    }

    void Node::AddChildren(std::vector<Node> children_to_copy) {
        for (auto child : children_to_copy) {
            AddChild(child);
        }
    }

    std::vector<NodePtr> Node::GetChildren(NodeType node_type) {
        return GetChildren(std::vector<NodeType> {node_type});
    }

    std::vector<NodePtr> Node::GetChildren(std::vector<NodeType> node_types) {
        std::vector<NodePtr> nodes;
        for (NodePtr p : children_) {
            bool in = false;
            for (NodeType t : node_types) {
                in |= t == p->GetType();
            }
            if (in) {
                nodes.push_back(p);
            }
        }
        return nodes;
    }

    std::vector<Node> Node::GetChildrenCopies(NodeType node_type) {
        std::vector<NodePtr> nodes = GetChildren(node_type);
        std::vector<Node> nodes_copies;
        for (NodePtr p : children_) {
            nodes_copies.push_back(*p);
        }
        return nodes_copies;
    }

    std::vector<Node> Node::GetChildrenCopies(std::vector<NodeType> node_types) {
        std::vector<NodePtr> nodes = GetChildren(node_types);
        std::vector<Node> nodes_copies;
        for (NodePtr p : children_) {
            nodes_copies.push_back(*p);
        }
        return nodes_copies;
    }

    std::vector<NodePtr> Node::GetChildren() {
        return children_;
    }

    std::vector<Node> Node::GetChildrenCopies() {
        std::vector<Node> v;
        for (auto p : children_) {
            v.push_back(*p);
        }
        return v;
    }

    NodeType Node::GetType() {
        return type_;
    }

    bool Node::IsLeaf() {
        return children_.empty();
    }

    std::vector<NodePtr> Node::operator[](NodeType node_type) {
        return GetChildren(node_type);
    }

    std::vector<NodePtr> Node::operator[](std::vector<NodeType> node_types) {
        return GetChildren(node_types);
    }

    std::vector<NodePtr> Node::operator[](bool) {
        return children_;
    }

    std::string Node::ToYAML() {
        std::stringstream s;
        ToYAMLIndented(s);
        return s.str();
    }

    void Node::ToYAMLIndented(std::stringstream & stream, int indent) {
        if (indent > 0) {
            stream << std::string(indent, ' ') << "- " << "Node:" << std::endl;
            indent += 2;
        } else {
            stream << "Node:" << std::endl;
        }
        indent += 2;
        stream << std::string(indent, ' ') << "Type: " << this->GetType() << std::endl;
        if (children_.empty()) {
            stream << std::string(indent, ' ') << "Children: []" << std::endl;
            return;
        }
        stream << std::string(indent, ' ') << "Children:" << std::endl;
        for (NodePtr p : children_) {
            p->ToYAMLIndented(stream, indent + 2);
        }
    }
}
