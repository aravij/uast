project(uast)
cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all"
        CACHE STRING "Compiler flags in asan build"
        FORCE)

add_subdirectory(source)
add_subdirectory(source/cpp-parser)
#add_subdirectory(source/java-parser)
#add_subdirectory(source/python-parser)
add_subdirectory(tests)
#find_package(Catch REQUIRED)
