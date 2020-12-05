#include "node.h"

std::shared_ptr<uast::Node> uast::Node::GetChild(std::string edge_name) {
    if (nodes_.count(edge_name) > 0) {
        return nodes_.find(edge_name)->second;
    }

    return nullptr;
}

uast::Node::NodeRange uast::Node::GetChildren(bool recursive) {
    if (!recursive) {
        return uast::Node::NodeRange(uast::Node::NodeIterator(nodes_.begin()),
                                     uast::Node::NodeIterator(nodes_.end()));
    }

    return uast::Node::NodeRange(uast::Node::RecursiveNodeIterator(nodes_.begin(), nodes_.end()),
                                 uast::Node::RecursiveNodeIterator(nodes_.end(), nodes_.end()));
}

uast::Node::NodeRange uast::Node::GetChildren(std::string edge_name) {
    return uast::Node::NodeRange(uast::Node::RecursiveNodeIterator(nodes_.begin(), nodes_.end()),
                                 uast::Node::RecursiveNodeIterator(nodes_.end(), nodes_.end()));
}

uast::Node::Node(std::string type, std::vector<std::string> edges_names,
                 std::vector<std::shared_ptr<Node>> children)
    : type_(type), nodes_() {
    if (edges_names.size() != children.size()) {
        throw std::runtime_error(
            "Number of keys (types): " + std::to_string(edges_names.size()) +
            " is not equal to number of nodes: " + std::to_string(children.size()));
    }

    for (size_t i = 0; i < children.size(); i++) {
        nodes_.emplace(edges_names[i], std::move(children[i]));
    }
}

uast::Node::Node(std::string type, std::vector<std::string> edges_names, std::vector<Node> children)
    : type_(type), nodes_() {
    if (edges_names.size() != children.size()) {
        throw std::runtime_error(
            "Number of keys (types): " + std::to_string(edges_names.size()) +
            " is not equal to number of nodes: " + std::to_string(children.size()));
    }

    for (size_t i = 0; i < children.size(); i++) {
        nodes_.emplace(edges_names[i], std::make_shared<Node>(children[i]));
    }
}

void uast::Node::AddChild(std::string edge_name, std::shared_ptr<Node> child) {
    nodes_.emplace(edge_name, std::move(child));
}

void uast::Node::AddChild(std::string edge_name, uast::Node child) {
    nodes_.emplace(edge_name, std::make_shared<uast::Node>(child));
}

std::string uast::Node::GetType() {
    return type_;
}

uast::Node::NodeIterator uast::Node::NodeIterator::operator++(int) {
    auto copy = uast::Node::NodeIterator(*this);
    cur_++;
    return copy;
}

std::shared_ptr<uast::Node> uast::Node::NodeIterator::operator*() {
    return cur_->second;
}

uast::Node *uast::Node::NodeIterator::operator->() {
    return cur_->second.get();
}

bool uast::Node::NodeIterator::operator==(const uast::Node::NodeIterator &other) {
    return cur_ == other.cur_;
}

bool uast::Node::NodeIterator::operator!=(const uast::Node::NodeIterator &other) {
    return cur_ != other.cur_;
}

uast::Node::NodeIterator &uast::Node::NodeIterator::operator++() {
    (*this)++;
    return (*this);
}

int uast::Node::NodeIterator::GetDepth() {
    return 0;
}

uast::Node::NodeIterator uast::Node::RecursiveNodeIterator::operator++(int) {
    auto copy = uast::Node::NodeIterator(*this);
    if (cur_stack_.back()->second->nodes_.empty()) {
        if (cur_stack_.back() == end_stack_.back()) {
            while (cur_stack_.back() == end_stack_.back()) {
                cur_stack_.pop_back();
                end_stack_.pop_back();
            }
        } else {
            cur_stack_[cur_stack_.size() - 1]++;
        }

        return copy;
    }
    cur_stack_.push_back(cur_stack_.back()->second->nodes_.begin());
    return copy;
}

std::shared_ptr<uast::Node> uast::Node::RecursiveNodeIterator::operator*() {
    return cur_stack_.back()->second;
}

uast::Node *uast::Node::RecursiveNodeIterator::operator->() {
    return cur_stack_.back()->second.get();
}

uast::Node::RecursiveNodeIterator::RecursiveNodeIterator(
    std::__detail::_Node_iterator<std::pair<const std::string, std::shared_ptr<Node>>, 0, 1> start,
    std::__detail::_Node_iterator<std::pair<const std::string, std::shared_ptr<Node>>, 0, 1> end)
    : NodeIterator(start) {
    cur_stack_.push_back(start);
    end_stack_.push_back(end);
}

int uast::Node::RecursiveNodeIterator::GetDepth() {
    return cur_stack_.size();
}

uast::Node::NodeIterator &uast::Node::RecursiveNodeIterator::operator++() {
    (*this)++;
    return (*this);
}
