cmake_minimum_required(VERSION 3.12)

project(
  args_library
  VERSION 0.0
  DESCRIPTION "library for parsing args")

add_library(
  libargs_obj_lib OBJECT)
target_sources(
  libargs_obj_lib
  PRIVATE "args.cpp")
target_include_directories(
  libargs_obj_lib
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_library(
  libargs_lib)
target_link_libraries(
  libargs_lib
  PUBLIC libargs_obj_lib)

add_library(
  libargs::lib ALIAS libargs_lib)

add_executable(
  libargs_test)
target_sources(
  libargs_test
  PRIVATE
  "args.test.cpp"
  "main.test.cpp")
target_link_libraries(
  libargs_test
  PRIVATE
  libargs::lib
  Boost::unit_test_framework
)

add_test(
  NAME libargs::test
  COMMAND libargs_test "--color_output=false")
