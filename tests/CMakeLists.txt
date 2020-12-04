project(tests)

set(SOURCE_EXE stub_entry.cpp)
set(SOURCE_REG_TESTS reg_test.cpp)
set(SOURCE_CPP_TESTS ../source/cpp-parser/test_cpp_parser.cpp)

#set(SOURCE_JAVA_TESTS ../source/catch.hpp)
#set(SOURCE_PYTHON_TESTS ../source/catch.hpp)

set(SOURCE_UAST_TESTS ../source/test_uast.cpp)

add_executable(stub_entry ${SOURCE_EXE})
target_link_libraries(stub_entry uast_core)
target_include_directories(stub_entry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../source)

add_executable(reg_test ${SOURCE_REG_TESTS})
target_link_libraries(reg_test ${CONAN_LIBS})
target_link_libraries(reg_test uast_core)
target_include_directories(reg_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../source)

add_executable(test_cpp_parser ${SOURCE_CPP_TESTS})
target_link_libraries(test_cpp_parser ${CONAN_LIBS})
target_link_libraries(test_cpp_parser cpp_parser)
target_include_directories(test_cpp_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../source/cpp-parser)

#add_executable(test_java_parser ${SOURCE_JAVA_TESTS})
#target_link_libraries(test_java_parser LINK_PUBLIC java_parser)
#target_include_directories(test_java_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../source/java-parser)
#
#add_executable(test_python_parser ${SOURCE_PYTHON_TESTS})
#target_link_libraries(test_python_parser LINK_PUBLIC python_parser)
#target_include_directories(test_python_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../source/python-parser)

add_executable(test_uast ${SOURCE_UAST_TESTS})

target_link_libraries(test_uast uast_core)
target_link_libraries(test_uast ${CONAN_LIBS})
#target_link_libraries(test_uast LINK_PUBLIC cpp_parser)
#target_link_libraries(test_uast LINK_PUBLIC java_parser)
#target_link_libraries(test_uast LINK_PUBLIC python_parser)
target_include_directories(test_uast PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../source)
#target_include_directories(test_uast PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../source/cpp-parser)
#target_include_directories(test_uast PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../source/java-parser)
#target_include_directories(test_uast PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../source/python-parser)
