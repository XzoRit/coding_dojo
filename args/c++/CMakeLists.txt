cmake_minimum_required(VERSION 3.10)

project(args_kata
        VERSION 0.0
        DESCRIPTION "an implementation of the args kata in c++")

enable_testing()

add_subdirectory(args)
add_subdirectory(libargs)
add_subdirectory(external)
