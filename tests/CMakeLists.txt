project(tests)

set(SOURCE_EXE stub_test.cpp)

add_executable(tests ${SOURCE_EXE})
target_link_libraries(tests LINK_PUBLIC uast_core)
target_link_libraries(tests LINK_PUBLIC cpp_parser)
target_link_libraries(tests LINK_PUBLIC java_parser)
target_link_libraries(tests LINK_PUBLIC python_parser)
target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../source)
target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../source/cpp-parser)
target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../source/java-parser)
target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../source/python-parser)
