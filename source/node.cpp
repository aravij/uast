#include "node.h"

// Node

std::shared_ptr<uast::Node> uast::Node::GetChild(std::string edge_name) {
    if (children_.count(edge_name) > 0) {
        return children_.find(edge_name)->second;
    }

    return nullptr;
}

uast::Node::Node(std::string type, std::vector<std::string> edges_names,
                 std::vector<std::shared_ptr<Node>> children)
    : type_(type), children_() {
    if (edges_names.size() != children.size()) {
        throw std::runtime_error(
            "Number of keys (types): " + std::to_string(edges_names.size()) +
            " is not equal to number of nodes: " + std::to_string(children.size()));
    }

    for (size_t i = 0; i < children.size(); i++) {
        children_.emplace(edges_names[i], std::move(children[i]));
    }
}

uast::Node::Node(std::string type, std::vector<std::string> edges_names, std::vector<Node> children)
    : type_(type), children_() {
    if (edges_names.size() != children.size()) {
        throw std::runtime_error(
            "Number of keys (types): " + std::to_string(edges_names.size()) +
            " is not equal to number of nodes: " + std::to_string(children.size()));
    }

    for (size_t i = 0; i < children.size(); i++) {
        children_.emplace(edges_names[i], std::make_shared<Node>(children[i]));
    }
}

void uast::Node::AddChild(std::string edge_name, std::shared_ptr<Node> child) {
    children_.emplace(edge_name, std::move(child));
}

void uast::Node::AddChild(std::string edge_name, uast::Node child) {
    children_.emplace(edge_name, std::make_shared<uast::Node>(child));
}

std::string uast::Node::GetType() {
    return type_;
}

bool uast::Node::IsLeaf() {
    return children_.empty();
}

std::shared_ptr<uast::Node> uast::Node::operator[](std::string edge_name) {
    return GetChild(edge_name);
}

uast::Node::Node(std::string type) : type_(type), children_() {
}

uast::Node::DFSRange uast::Node::DFS() {
    return uast::Node::DFSRange(this);
}

uast::Node::DFSIterator::DFSIterator(std::stack<std::pair<Iterator, Iterator>> *stack)
    : stack_(stack) {
    PopEnds();
    GoDown();
    //    PopEnds();
}

uast::Node::DFSIterator &uast::Node::DFSIterator::operator++() {
    if (stack_->empty()) {
        return *this;
    }

    if (stack_->top().first == stack_->top().second) {
        stack_->pop();
        if (stack_->empty()) {
            return *this;
        }
        stack_->top().first++;
        GoDown();
        return *this;
    }

    stack_->top().first++;
    return *this;
}

uast::Node::DFSIterator uast::Node::DFSIterator::operator++(int) {
    uast::Node::DFSIterator old = *this;
    ++(*this);
    return old;
}

bool uast::Node::DFSIterator::operator==(const uast::Node::DFSIterator &other) const {
    bool empty =
        stack_->empty() || (stack_->size() == 1 && stack_->top().first == stack_->top().second);
    bool other_empty =
        other.stack_->empty() ||
        (other.stack_->size() == 1 && other.stack_->top().first == other.stack_->top().second);

    if (other_empty != empty) {
        return false;
    }

    if (other_empty == empty) {
        return true;
    }

    auto *my_stack = stack_;
    auto *other_stack = other.stack_;

    while (!other_stack->empty() && !my_stack->empty()) {
        if (other_stack->top().first != my_stack->top().first) {
            return false;
        }
        other_stack->pop();
        my_stack->pop();
        if (other.stack_->empty() != stack_->empty()) {
            return false;
        }
    }

    return true;
}

uast::Node::EdgeNodePair uast::Node::DFSIterator::operator*() {
    if (stack_->top().first == stack_->top().second) {
        auto top = stack_->top();
        stack_->pop();
        auto p = stack_->top();
        stack_->push(top);
        return *p.first;
    }

    return *stack_->top().first;
}

uast::Node::Iterator uast::Node::DFSIterator::operator->() {
    if (stack_->top().first == stack_->top().second) {
        auto top = stack_->top();
        stack_->pop();
        auto p = stack_->top();
        stack_->push(top);
        return p.first;
    }

    return stack_->top().first;
}

bool uast::Node::DFSIterator::operator!=(const uast::Node::DFSIterator &other) const {
    return !(*this == other);
}

void uast::Node::DFSIterator::GoDown() {
    while (stack_ && !stack_->empty() && stack_->top().first != stack_->top().second &&
           !stack_->top().first->second->children_.empty()) {
        stack_->push(std::make_pair(stack_->top().first->second->children_.begin(),
                                    stack_->top().first->second->children_.end()));
    }
}

void uast::Node::DFSIterator::PopEnds() {
    while (stack_ && !stack_->empty() && stack_->top().first == stack_->top().second) {
        stack_->pop();
    }
}

uast::Node::DFSRange::DFSRange(uast::Node *node) : stack_() {
    stack_.emplace(node->children_.begin(), node->children_.end());
}

uast::Node::DFSIterator uast::Node::DFSRange::begin() {  // NOLINT
    return uast::Node::DFSIterator(&stack_);
}

uast::Node::DFSIterator uast::Node::DFSRange::end() {  // NOLINT
    return uast::Node::DFSIterator(&empty_stack_);
}

// uast::Node::DFSQueryIterator::DFSQueryIterator(std::stack<std::pair<Iterator, Iterator>> *node,
// std::function<bool(size_t, EdgeNodePair)> predicate) : uast::Node::DFSIterator(node),  {
//
//}

// uast::Node::DFSQueryIterator::DFSQueryIterator(std::function<bool(uint64_t,
//                                                                  std::pair<std::basic_string<char>,
//                                                                  std::shared_ptr<Node>>)>
//                                                                  predicate,
//                                               std::stack<std::pair<Iterator, Iterator>> *stack) :
//                                               DFSIterator(stack), predicate_(predicate) {
//    bool empty = stack_->empty() || (stack_->size() == 1 && stack_->top().first ==
//    stack_->top().second); while (!empty && !predicate_(stack_->size())) {
//        (this->operator++());
//    }
//}
