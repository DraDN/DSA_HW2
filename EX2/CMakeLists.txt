add_library(RK STATIC src/RegistryOfKnights.cpp src/RegistryOfKnightsUI.cpp)
target_include_directories(RK PUBLIC include)
target_link_libraries(RK PUBLIC TOOLS)

add_subdirectory(tests)