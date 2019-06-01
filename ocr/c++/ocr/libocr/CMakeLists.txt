cmake_minimum_required(VERSION 3.12)

project(
  ocr_library
  VERSION 0.0
  DESCRIPTION "library for parsing ocr")

add_library(
  libocr_obj_lib OBJECT)
target_sources(
  libocr_obj_lib
  PRIVATE "ocr.cpp")
target_include_directories(
  libocr_obj_lib
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_library(
  libocr_lib)
target_link_libraries(
  libocr_lib
  PUBLIC libocr_obj_lib)

add_library(
  libocr::lib ALIAS libocr_lib)

add_executable(
  libocr_test)
target_sources(
  libocr_test
  PRIVATE
  "ocr.test.cpp"
  "main.test.cpp")
target_compile_features(
  libocr_test
  PRIVATE
  cxx_std_20)
target_link_libraries(
  libocr_test
  PRIVATE
  libocr::lib
  Boost::unit_test_framework
)

add_test(
  NAME libocr::test
  COMMAND libocr_test "--color_output=false")
