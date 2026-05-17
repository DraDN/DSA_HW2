add_executable(city_simulation src/main.cpp src/CityGraph.cpp src/CityController.cpp)
target_include_directories(city_simulation PRIVATE include)

add_library(city_graph_lib STATIC src/CityGraph.cpp)
target_include_directories(city_graph_lib PUBLIC include)

foreach(test connectivity constraints edge_cases energy_limit)
    add_executable(test_${test} tests/test_${test}.cpp)
    target_link_libraries(test_${test} PRIVATE city_graph_lib)
endforeach()

foreach(test connectivity constraints edge_cases energy_limit)
    add_test(NAME ${test} COMMAND test_${test})
endforeach()

add_custom_target(
    run_ex1
    COMMAND city_simulation
    DEPENDS city_graph_lib
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    USES_TERMINAL
)