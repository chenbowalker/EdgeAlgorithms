cmake_minimum_required(VERSION 3.9)
project(hello)

set(CMAKE_CXX_STANDARD 11)

add_executable(hello main.cpp hashmap.h hashmap.cpp)