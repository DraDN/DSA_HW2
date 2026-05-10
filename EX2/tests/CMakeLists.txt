add_executable(TEST test.cpp)
target_link_libraries(TEST PUBLIC RK)

add_test(NAME TEST_EX1 COMMAND TEST)