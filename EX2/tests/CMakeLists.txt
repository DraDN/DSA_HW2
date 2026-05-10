add_executable(TEST_HOUSE_SEARCH test_house_search.cpp)
target_link_libraries(TEST_HOUSE_SEARCH PUBLIC RK)
target_include_directories(TEST_HOUSE_SEARCH PRIVATE ./)

add_executable(TEST_TREE_INFO test_tree_info.cpp)
target_link_libraries(TEST_TREE_INFO PUBLIC RK)
target_include_directories(TEST_TREE_INFO PRIVATE ./)

add_test(NAME TEST_HOUSE_SEARCH COMMAND TEST_HOUSE_SEARCH)
add_test(NAME TEST_TREE_INFO COMMAND TEST_TREE_INFO)