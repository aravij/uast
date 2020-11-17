#include "node.h"


std::shared_ptr<uast::Node> uast::Node::GetChild(std::string type) {
    if (nodes_.count(type) > 0) {
        return nodes_.find(type)->second;
    }

    return nullptr;
}

template <typename T>
T uast::Node::GetChildValue(std::string type) {
    if (nodes_.count(type) > 0) {
        if (std::shared_ptr<Leaf<T>> leaf = std::dynamic_pointer_cast<Leaf<T>>()) {
            return leaf->GetValue();
        }
    }

    throw std::runtime_error("No such child or it is not leaf of type <T>");
}

uast::Node::NodeRange uast::Node::GetChildren(bool recursive) {
    return uast::Node::NodeRange(NodeIterator(), NodeIterator());
}

uast::Node::NodeRange uast::Node::GetChildren(std::string type) {
    return uast::Node::NodeRange(uast::Node::NodeIterator(), uast::Node::NodeIterator());
}

template<typename M>
std::shared_ptr<uast::Leaf<M>> uast::Node::GetLeaf(std::string type) {
    if (nodes_.count(type) > 0) {
        if (std::shared_ptr<Leaf<M>> leaf = std::dynamic_pointer_cast<Leaf<M>>()) {
            return leaf;
        }
    }

    throw std::runtime_error("No such child or it is not leaf of type <T>");
}

std::shared_ptr<uast::Node> uast::Node::GetParent() {
    return std::shared_ptr<uast::Node>();
}

uast::Node::Node(std::vector<std::string> types,
                 std::vector<std::shared_ptr<Node>> children,
                 std::shared_ptr<Node> parent) : parent_(parent) {
    if (types.size() != children.size()) {
        throw std::runtime_error("Number of keys (types): " + std::to_string(types.size()) +
                                 " is not equal to number of nodes: " + std::to_string(children.size()));
    }

    for (size_t i = 0; i < children.size(); i++) {
        nodes_.emplace(types[i], std::move(children[i]));
    }
}

template<typename T>
void uast::Node::AddLeafChild(std::string type, uast::Leaf<T> child) {
    nodes_.emplace(type, std::make_shared<uast::Node>(child));
}

void uast::Node::AddChild(std::string type, std::shared_ptr<Node> child) {
    nodes_.emplace(type, std::move(child));
}

void uast::Node::AddNodeChild(std::string type, uast::Node child) {
    nodes_.emplace(type, std::make_shared<uast::Node>(child));
}

template<typename T>
T uast::Leaf<T>::GetValue() {
    return value_;
}
