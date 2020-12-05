#include <memory>
#include <iterator>
#include <unordered_map>
#include <any>
#include <vector>

namespace uast {
    class Node {
        std::unordered_multimap<std::string, std::shared_ptr<Node>> nodes_;
        std::string type_;

    public:
        class NodeIterator : std::iterator<std::forward_iterator_tag, Node> {
            std::unordered_multimap<std::string, std::shared_ptr<Node>>::iterator cur_;

        public:
            NodeIterator(std::unordered_multimap<std::string, std::shared_ptr<Node>>::iterator start) : cur_(start) {
            }

            virtual NodeIterator operator++(int);

            virtual NodeIterator &operator++();

            virtual std::shared_ptr<Node> operator*();

            virtual Node *operator->();

            virtual bool operator==(const NodeIterator &other);

            virtual bool operator!=(const NodeIterator &other);

            virtual int GetDepth();

            virtual ~NodeIterator() = default;
        };

        class RecursiveNodeIterator : public NodeIterator {
            std::vector<std::unordered_multimap<std::string, std::shared_ptr<Node>>::iterator> cur_stack_;
            std::vector<std::unordered_multimap<std::string, std::shared_ptr<Node>>::iterator> end_stack_;
        public:
            RecursiveNodeIterator(std::unordered_multimap<std::string, std::shared_ptr<Node>>::iterator begin,
                                  std::unordered_multimap<std::string, std::shared_ptr<Node>>::iterator end);

            virtual NodeIterator operator++(int) override;

            virtual NodeIterator &operator++() override;

            virtual std::shared_ptr<Node> operator*() override;

            virtual Node *operator->() override;

            virtual int GetDepth() override;
        };

        class NodeRange {
            NodeIterator begin_;
            NodeIterator end_;

        public:
            NodeIterator begin() { // NOLINT
                return begin_;
            }

            NodeIterator end() { // NOLINT
                return end_;
            }

            NodeRange(NodeIterator begin, NodeIterator end) : begin_(begin), end_(end) {
            }
        };

        Node(std::string type) : type_(type), nodes_() {
        }

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

        bool IsLeaf() {
            return nodes_.empty();
        }

        // Returns children or, optionally, all inheritors
        NodeRange GetChildren(bool recursive = false);

        NodeRange GetChildren(std::string edge_name);

        std::shared_ptr<Node> operator[](std::string edge_name) {
            return GetChild(edge_name);
        }

        virtual ~Node() = default;
    };
}
