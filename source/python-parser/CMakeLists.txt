project(python_parser)

set(SOURCE_LIB python_parser.h python_parser_stub.cpp test-python-parser.cpp)

add_library(python_parser STATIC ${SOURCE_LIB})
target_include_directories(python_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_python_parser test-python-parser.cpp ../catch.hpp)