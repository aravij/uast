project(tests)

set(SOURCE_EXE stub_entry.cpp)
set(SOURCE_REG_TESTS reg_test.cpp ../source/catch.hpp)

add_executable(stub_entry ${SOURCE_EXE})
target_link_libraries(stub_entry LINK_PUBLIC uast_core)
target_include_directories(stub_entry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../source)

add_executable(reg_test ${SOURCE_REG_TESTS})
target_link_libraries(reg_test LINK_PUBLIC uast_core)
target_include_directories(reg_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../source)
