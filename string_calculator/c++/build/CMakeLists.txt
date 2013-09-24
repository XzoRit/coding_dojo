cmake_minimum_required(VERSION 2.8)

project(string_calculator)

include_directories(".." "../../../../c++/catch/single_include" "../../../../c++/boost")

set (${PROJECT_NAME}_headers "../lib/convert.hpp" "../lib/str_utils.hpp")
set (${PROJECT_NAME}_sources "../test/main.cpp")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage --coverage -fverbose-asm -save-temps")

add_executable(${PROJECT_NAME}_cpploop
  ${${PROJECT_NAME}_headers} "../cpploop/string_calculator.hpp"
  ${${PROJECT_NAME}_sources})
add_executable(${PROJECT_NAME}_cpp03
  ${${PROJECT_NAME}_headers} "../cpp03/string_calculator.hpp"
  ${${PROJECT_NAME}_sources})
add_executable(${PROJECT_NAME}_boost
  ${${PROJECT_NAME}_headers}  "../boost/string_calculator.hpp"
  ${${PROJECT_NAME}_sources})
add_executable(${PROJECT_NAME}_cpp11
  ${${PROJECT_NAME}_headers} "../cpp11/string_calculator.hpp"
  ${${PROJECT_NAME}_sources})

set_property(TARGET ${PROJECT_NAME}_cpploop APPEND PROPERTY INCLUDE_DIRECTORIES "../cpploop")
set_property(TARGET ${PROJECT_NAME}_cpp03 APPEND PROPERTY INCLUDE_DIRECTORIES "../cpp03")
set_property(TARGET ${PROJECT_NAME}_boost APPEND PROPERTY INCLUDE_DIRECTORIES "../boost")
set_property(TARGET ${PROJECT_NAME}_cpp11 APPEND PROPERTY INCLUDE_DIRECTORIES "../cpp11")

set_property(TARGET ${PROJECT_NAME}_cpp11 APPEND PROPERTY COMPILE_FLAGS "-std=c++11")
