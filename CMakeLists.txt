cmake_minimum_required(VERSION 2.8.9)

project(ContextControl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

add_subdirectory(extern)
add_subdirectory(src)
add_subdirectory(tests)

