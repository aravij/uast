project(uast)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(source)
add_subdirectory(source/cpp-parser)
add_subdirectory(source/java-parser)
add_subdirectory(source/python-parser)
add_subdirectory(tests)
#find_package(Catch REQUIRED)