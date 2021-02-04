#include <memory>
#include <iterator>
#include <unordered_map>
#include <any>
#include <vector>
#include <stack>
#include <functional>
#include "node_type.h"

namespace uast {
    class Node {
        NodeType kek_ = Expression;
        std::unordered_multimap<std::string, std::shared_ptr<Node>> children_;
        using EdgeNodePair = std::pair<std::string, std::shared_ptr<Node>>;
        using Iterator = std::unordered_multimap<std::string, std::shared_ptr<Node>>::iterator;
        std::string type_;

    public:
        class DFSIterator {
        protected:
            std::stack<std::pair<Iterator, Iterator>> *stack_;

            void GoDown();

            void PopEnds();

        public:
            DFSIterator(std::stack<std::pair<Iterator, Iterator>> *stack);

            DFSIterator &operator++();

            DFSIterator operator++(int);

            bool operator==(const DFSIterator &other) const;

            bool operator!=(const DFSIterator &other) const;

            EdgeNodePair operator*();

            Iterator operator->();
        };

        class DFSRange {
        protected:
            std::stack<std::pair<Iterator, Iterator>> stack_;
            std::stack<std::pair<Iterator, Iterator>> empty_stack_;

        public:
            DFSRange(Node *node);

            DFSIterator begin(); // NOLINT

            DFSIterator end(); // NOLINT
        };

        class DFSQueryIterator : DFSIterator {
        protected:
            std::function<bool(size_t, size_t, EdgeNodePair)> predicate_;

        public:
            // Enter only nodes, which are fitting predicate
            DFSQueryIterator(std::function<bool(uint64_t, uint64_t,
                                                std::pair<std::basic_string<char>, std::shared_ptr<Node>>)> predicate,
                             std::stack<std::pair<Iterator, Iterator>> *stack);

            DFSIterator &operator++();

//            DFSIterator operator++(int);

//            bool operator== (const DFSIterator& other) const;

//            EdgeNodePair operator* ();

//            EdgeNodePair& operator->();
        };

        class DFSQueryRange {
            std::function<bool(size_t, size_t, EdgeNodePair)> predicate_;
        public:
            DFSQueryRange(Node *node, std::function<bool(size_t, EdgeNodePair)> predicate);

            DFSIterator begin(); // NOLINT

            DFSIterator end(); // NOLINT
        };

        Node(std::string type);

        Node(std::string type,
             std::vector<std::string> edges_names,
             std::vector<std::shared_ptr<Node>> children);

        Node(std::string type,
             std::vector<std::string> edges_names,
             std::vector<Node> children);

        void AddChild(std::string edge_name, std::shared_ptr<Node> child);

        void AddChild(std::string edge_name, Node child);

        std::shared_ptr<Node> GetChild(std::string edge_name);

        std::string GetType();

        bool IsLeaf();

        std::shared_ptr<Node> operator[](std::string edge_name);

        DFSRange DFS();

        virtual ~Node() = default;
    };
}




