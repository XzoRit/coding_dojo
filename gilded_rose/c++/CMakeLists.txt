cmake_minimum_required(VERSION 3.2)

project(gilded_rose)

include_directories("/opt/local/include")

set (${PROJECT_NAME}_headers "")
set (${PROJECT_NAME}_sources
  "article.cpp"
  "aged_brie.cpp"
  "backstage_pass.cpp"
  "sulfuras.cpp"
  "conjured.cpp")

add_executable(${PROJECT_NAME}_main
  ${${PROJECT_NAME}_headers} ""
  ${${PROJECT_NAME}_sources} "main.cpp")

add_executable(${PROJECT_NAME}_test
  ${${PROJECT_NAME}_headers} ""
  ${${PROJECT_NAME}_sources} "test.cpp")
