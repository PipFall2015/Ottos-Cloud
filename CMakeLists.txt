cmake_minimum_required(VERSION 2.8.4)
project(PipSpring2015)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    follow.cpp
    follow.hh
    main.cpp)

add_executable(PipSpring2015 ${SOURCE_FILES})