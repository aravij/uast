project(java_parser)

set(SOURCE_LIB java_parser.h java_parser_stub.cpp)

add_library(java_parser STATIC ${SOURCE_LIB})
target_include_directories(java_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#add_executable(test_java_parser ) TODO: add unit tests