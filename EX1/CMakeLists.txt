cmake_minimum_required(VERSION 3.10)
project(RobotRoadModel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(city_simulation main.cpp CityGraph.cpp CityController.cpp
)