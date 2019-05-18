cmake_minimum_required(VERSION 3.12)

project(
  args_executeable
  VERSION 0.0
  DESCRIPTION "executable args application")

add_executable(
  args_exe)
target_sources(
  args_exe
  PRIVATE
  "main.cpp")
target_link_libraries(
  args_exe
  PRIVATE
  libargs::lib
  Boost::program_options)

add_test(
  NAME args::exe
  COMMAND args_exe "--help")
