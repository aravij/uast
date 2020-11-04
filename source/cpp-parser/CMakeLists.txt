project(cpp_parser)

set(SOURCE_LIB cpp_parser.h cpp_parser_stub.cpp)
set(SOURCE_TESTS test_cpp_parser.cpp ../catch.hpp)

add_library(cpp_parser STATIC ${SOURCE_LIB})
target_include_directories(cpp_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_cpp_parser ${SOURCE_TESTS})