cmake_minimum_required(VERSION 3.12)

project(
  ocr_executeable
  VERSION 0.0
  DESCRIPTION "executable ocr application")

add_executable(
  ocr_exe)
target_sources(
  ocr_exe
  PRIVATE
  "main.cpp")
target_link_libraries(
  ocr_exe
  PRIVATE
  libocr::lib
  Boost::program_options)

add_test(
  NAME ocr::exe
  COMMAND ocr_exe "--help")
