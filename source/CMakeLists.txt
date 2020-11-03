project(uast_core)

set(SOURCE_LIB uast.h uast_stub.cpp)

add_library(uast_core STATIC ${SOURCE_LIB})
target_include_directories(uast_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#add_executable(test_uast ) TODO: add unit tests