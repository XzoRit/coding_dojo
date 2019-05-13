cmake_minimum_required(VERSION 3.10)

project(
  args_executeable
  VERSION 0.0
  DESCRIPTION "executable args application")

add_executable(
  args_exe
  main.cpp)

target_link_libraries(
  args_exe
  PRIVATE libargs::lib)
