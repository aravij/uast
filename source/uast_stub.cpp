#include <string>
#include <functional>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/detail/read_graphviz_new.hpp>

#include "uast.h"

namespace uast {

namespace {
PLanguage detectLang(const std::string& filePath) {
    std::string fileExtension = filePath.substr(filePath.find_last_of('.'));
    for (auto& [pLang, setOfExtensions] : extensions) {
        if (setOfExtensions.count(fileExtension)) {
            return pLang;
        }
    }
    return None;
}

std::string getRunner(const PLanguage& pLang, const std::string& javaVmPath,
                      const std::string& pythonVmPath) {

    const std::string runCppParser = "cpp_parser/cpp_parser.exe",
                      runJavaParser = javaVmPath + "java -jar java_parser/java_parser.jar",
                      runPythonParser = pythonVmPath + "python python_parser/python_parser.py";

    switch (pLang) {
        case Cpp:
            return runCppParser;
        case Java:
            return runJavaParser;
        case Python:
            return runPythonParser;
    }
}
}  // namespace

Node build(const std::string& filePath, std::string javaVmPath, std::string pythonVmPath) {

    // Add backslash in the end of path
    if (!javaVmPath.empty() && javaVmPath.back() != '/')
        javaVmPath += '/';
    if (!pythonVmPath.empty() && pythonVmPath.back() != '/')
        pythonVmPath += '/';

    // Detecting language
    PLanguage pLang = detectLang(filePath);
    if (pLang == None) {
        throw std::runtime_error("Incorrect input file\n");
    }

    std::string runParserCommand = getRunner(pLang, javaVmPath, pythonVmPath);

    system(runParserCommand.c_str());

    const std::string gvFilePath = "graph.dot";  // Where is parser result?

    // Parse .dot to boost::graph
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, DotVertex, DotEdge>
        graph_t;
    using vertex_t = boost::graph_traits<graph_t>::vertex_descriptor;
    using edge_t = boost::graph_traits<graph_t>::edge_descriptor;

    graph_t graph(0);

    boost::dynamic_properties dp(boost::ignore_other_properties);
    dp.property("type", get(&DotVertex::type, graph));
    dp.property("name", get(&DotEdge::name, graph));

    boost::property_map<graph_t, std::string DotVertex::*>::type typeMap =
        get(&DotVertex::type, graph);

    boost::property_map<graph_t, std::string DotEdge::*>::type nameMap = get(&DotEdge::name, graph);

    std::ifstream gvFile(gvFilePath);

    bool status = read_graphviz(gvFile, graph, dp);

    if (!status) {
        throw std::runtime_error("Incorrect .dot file");
    }

    std::unordered_map<vertex_t, std::shared_ptr<Node>> nodes;
    std::unordered_map<std::shared_ptr<Node>, int> degrees;

    boost::graph_traits<graph_t>::vertex_iterator vIt, end;
    boost::graph_traits<graph_t>::out_edge_iterator eIt, edge_end;

    // Parse boost::graph to uast
    for (boost::tie(vIt, end) = boost::vertices(graph); vIt != end; vIt++) {
        vertex_t v = *vIt;
        if (nodes.find(v) == nodes.end()) {
            nodes[v] = std::make_shared<Node>(typeMap[v]);
            degrees[nodes[v]] = 0;
        }

        for (boost::tie(eIt, edge_end) = boost::out_edges(*vIt, graph); eIt != edge_end; eIt++) {
            vertex_t to = boost::target(*eIt, graph);
            if (nodes.find(to) == nodes.end()) {
                nodes[to] = std::make_shared<Node>(typeMap[to]);
            }
            nodes[v]->AddChild(nameMap[*eIt], nodes[to]);
            degrees[nodes[to]]++;
        }
    }

    auto rootP =
        std::find_if(degrees.begin(), degrees.end(), [](const auto& p) { return p.second == 0; });

    return *rootP->first;
}

std::string Stub() {
    return "-- Uast loaded successfully";
}
}  // namespace uast
