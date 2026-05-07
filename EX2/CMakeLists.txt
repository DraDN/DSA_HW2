# add_library(TLM STATIC src/TimeLineManager.cpp)
# target_include_directories(TLM PUBLIC include)
# target_link_libraries(TLM PUBLIC TOOLS)

add_subdirectory(tests)

# add_custom_target(
    # run_ex2
    # COMMAND TEST_TLM
    # DEPENDS TLM
    # WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    # USES_TERMINAL
# )