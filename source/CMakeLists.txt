project(uast_core)

set(SOURCE_LIB uast.h uast_stub.cpp)

add_library(uast_core STATIC ${SOURCE_LIB})

target_link_libraries(uast_core LINK_PUBLIC cpp_parser)
target_link_libraries(uast_core LINK_PUBLIC java_parser)
target_link_libraries(uast_core LINK_PUBLIC python_parser)
target_include_directories(uast_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cpp-parser)
target_include_directories(uast_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/java-parser)
target_include_directories(uast_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/python-parser)

