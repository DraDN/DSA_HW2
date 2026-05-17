cmake_minimum_required(VERSION 3.10)
project(RobotRoadModel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(city_simulation src/main.cpp src/CityGraph.cpp src/CityController.cpp)
target_include_directories(city_simulation PRIVATE include)

add_library(city_graph_lib STATIC src/CityGraph.cpp)
target_include_directories(city_graph_lib PUBLIC include)

foreach(test connectivity constraints edge_cases energy_limit)
    add_executable(test_${test} tests/test_${test}.cpp)
    target_link_libraries(test_${test} PRIVATE city_graph_lib)
endforeach()

enable_testing()
foreach(test connectivity constraints edge_cases energy_limit)
    add_test(NAME ${test} COMMAND test_${test})
endforeach()