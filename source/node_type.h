#include <vector>

#define MAKE_ENUM(name, ...) enum class name { __VA_ARGS__, __COUNT}; \
inline std::ostream& operator<<(std::ostream& os, name value) { \
std::string enumName = #name; \
std::string str = #__VA_ARGS__; \
int len = str.length(); \
std::vector<std::string> strings; \
std::ostringstream temp; \
for(int i = 0; i < len; i ++) { \
if(isspace(str[i])) continue; \
        else if(str[i] == ',') { \
        strings.push_back(temp.str()); \
        temp.str(std::string());\
        } \
        else temp<< str[i]; \
} \
strings.push_back(temp.str()); \
os << strings[static_cast<int>(value)]; \
return os;}

namespace uast {
    MAKE_ENUM(NodeType,
              Expression,
              Statement,
              FunctionDefinition,
              ClassDefinition
    )

    inline std::vector<NodeType> operator&(NodeType lhs, NodeType rhs) {
        return std::vector<NodeType>{lhs, rhs};
    }

    inline std::vector<NodeType> operator&(std::vector<NodeType> lhs, NodeType rhs) {
        lhs.push_back(rhs);
        return lhs;
    }
}
