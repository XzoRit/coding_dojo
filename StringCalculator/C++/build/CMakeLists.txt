cmake_minimum_required(VERSION 2.8)

project(string_calculator)

#include_directories(".." "../cpp03" "../../../../C++/catch/single_include")
#include_directories(".." "../boost" "../../../../C++/catch/single_include" "../../../../C++/boost_1_53_0")
include_directories(".." "../cpp11" "../../../../C++/catch/single_include" "../../../../C++/boost_1_53_0")

INCLUDE(CMakeForceCompiler) 
CMAKE_FORCE_CXX_COMPILER(clang CLang)

SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
#add_definitions(-DBOOST_RESULT_OF_USE_DECLTYPE)

add_executable(string_calculator_cpp11 ../test/main.cpp)
