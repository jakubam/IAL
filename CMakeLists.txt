cmake_minimum_required(VERSION 3.15)
project(IAL)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(IAL
        graph.c
        graph.h
        main.c)
