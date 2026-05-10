add_executable(TEST test.cpp)
target_link_libraries(TEST PUBLIC RK)

add_custom_target(
    run_test_ex1
    DEPENDS TEST
    COMMAND sh -c "$<TARGET_FILE:TEST><${CMAKE_SOURCE_DIR}/EX2/test.in"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/EX2
    USES_TERMINAL
)

add_executable(TEST_HOUSE_SEARCH test_house_search.cpp)
target_link_libraries(TEST_HOUSE_SEARCH PUBLIC RK)
target_include_directories(TEST_HOUSE_SEARCH PRIVATE ./)

add_executable(TEST_RANGE_SEARCH test_search_by_range.cpp)
target_link_libraries(TEST_RANGE_SEARCH PUBLIC RK)
target_include_directories(TEST_RANGE_SEARCH PRIVATE ./)

add_executable(TEST_TREE_INFO test_tree_info.cpp)
target_link_libraries(TEST_TREE_INFO PUBLIC RK)
target_include_directories(TEST_TREE_INFO PRIVATE ./)

add_test(NAME TEST_HOUSE_SEARCH COMMAND TEST_HOUSE_SEARCH)
add_test(NAME TEST_TREE_INFO COMMAND TEST_TREE_INFO)
add_test(NAME TEST_RANGE_SEARCH COMMAND TEST_RANGE_SEARCH)