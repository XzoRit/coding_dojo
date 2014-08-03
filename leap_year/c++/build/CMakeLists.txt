cmake_minimum_required(VERSION 2.8)

project(leap_year)

include_directories("/opt/local/include")
link_directories("/opt/local/lib")

set (${PROJECT_NAME}_headers "")
set (${PROJECT_NAME}_sources "../leap_year.cpp")

add_executable(${PROJECT_NAME}
  ${${PROJECT_NAME}_headers}
  ${${PROJECT_NAME}_sources})

set (${PROJECT_NAME}_libs
	libboost_program_options-mt.a
	libboost_system-mt.a
	libboost_filesystem-mt.a)

target_link_libraries(${PROJECT_NAME}
	${${PROJECT_NAME}_libs})
