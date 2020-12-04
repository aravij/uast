#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>
#include "cpp_parser.h"
#include "node.h"

// #include "java_parser.h"
// #include "python_parser.h"

namespace uast {
    namespace {
        enum PLanguage { Cpp, Java, Python, None };

        std::unordered_map<PLanguage, std::unordered_set<std::string>> extensions = {
            {Cpp, {".CPP", ".cpp", ".cxx", ".CXX", ".hpp", ".hxx", ".Hxx", ".HXX"}},
            {Java, {".java"}},
            {Python, {".py", ".py3"}}
        };

        PLanguage detectLang(const std::string& filePath);

        std::string getRunner(const PLanguage& pLang,
                              const std::string& javaVmPath,
                              const std::string& pythonVmPath);

        struct DotVertex {
            std::string type;
        };

        struct DotEdge {
            std::string name;
        };
    }


    Node build(const std::string& filePath,
               std::string javaVmPath   = "",
               std::string pythonVmPath = "");

    std::string Stub();
}
