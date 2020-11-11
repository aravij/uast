project(python_parser)

set(SOURCE_LIB python_parser.h python_parser_stub.cpp)
set(SOURCE_TESTS test_python_parser.cpp ../catch.hpp)

add_library(python_parser STATIC ${SOURCE_LIB})
target_include_directories(python_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
