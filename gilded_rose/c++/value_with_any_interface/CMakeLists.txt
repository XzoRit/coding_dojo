cmake_minimum_required(VERSION 3.2)

project(gilded_rose_value_with_any_interface)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../../doctest/doctest")

set (${PROJECT_NAME}_headers "")
set (${PROJECT_NAME}_sources "")

add_executable(${PROJECT_NAME}_main
  ${${PROJECT_NAME}_headers} ""
  ${${PROJECT_NAME}_sources} "gilded_rose.cpp")
