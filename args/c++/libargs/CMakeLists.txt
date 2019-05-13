cmake_minimum_required(VERSION 3.10)

add_library(
  libargs_obj_lib
  OBJECT "args.cpp")
target_include_directories(
  libargs_obj_lib
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_library(
  libargs_lib)
target_sources(
  libargs_lib
  PRIVATE $<TARGET_OBJECTS:libargs_obj_lib>)
target_include_directories(
  libargs_lib
  PUBLIC $<TARGET_PROPERTY:libargs_obj_lib,INTERFACE_INCLUDE_DIRECTORIES>)

add_library(
  libargs::lib ALIAS libargs_lib)
