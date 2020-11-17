#include <memory>
#include <iterator>
#include <unordered_map>
#include <any>
#include <vector>

namespace uast {
    class Node;

    template<typename T>
    class Leaf;

    class Node {
        std::unordered_multimap<std::string, std::shared_ptr<Node>> nodes_;
        std::weak_ptr<Node> parent_; // To avoid memory leak

    public:
        class NodeIterator : std::iterator<std::forward_iterator_tag, Node> {
        };

        class RecursiveNodeIterator : NodeIterator {
        };

        class FixedTypeNodeIterator : NodeIterator {
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

        Node(std::shared_ptr<Node> parent = std::shared_ptr<Node>()) : parent_(parent) {
        }

        Node(std::vector<std::string> types,
             std::vector<std::shared_ptr<Node>> children,
             std::shared_ptr<Node> parent = std::shared_ptr<Node>());

        void AddChild(std::string type, std::shared_ptr<Node> child);

        void AddNodeChild(std::string type, Node child);

        template<typename T>
        void AddLeafChild(std::string type, Leaf<T> child);

        std::shared_ptr<Node> GetParent();

        std::shared_ptr<Node> GetChild(std::string type);

        template <typename T>
        T  GetChildValue(std::string type);

        // Returns children or, optionally, all inheritors
        NodeRange GetChildren(bool recursive = false);

        NodeRange GetChildren(std::string type);

        template<typename M>
        std::shared_ptr<Leaf<M>> GetLeaf(std::string type);

        std::shared_ptr<Node> operator[](std::string type) {
            return GetChild(type);
        }

        template <typename T>
        T  operator()(std::string type) {
            return GetChildValue<T>(type);
        }

        virtual ~Node() = default;
    };

    template<typename T>
    class Leaf : Node {
        T value_;
    public:
        Leaf(T value, std::shared_ptr<Node> parent = std::shared_ptr<Node>()) : Node(parent), value_(std::move(value)) {
        }

        T GetValue();
    };
}
