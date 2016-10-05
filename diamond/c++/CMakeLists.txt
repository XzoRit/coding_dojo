cmake_minimum_required(VERSION 3.5)
project("diamond")

include_directories(SYSTEM /opt/local/include)

add_subdirectory("v1")
add_subdirectory("v2")
add_subdirectory("v3")
add_executable(diamond diamond.cpp)
target_link_libraries(diamond diamond_v1 diamond_v2 diamond_v3)

set_property(TARGET diamond PROPERTY CXX_STANDARD 14)
set_property(TARGET diamond PROPERTY CXX_STANDARD_REQUIRED ON)
