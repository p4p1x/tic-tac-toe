cmake_minimum_required(VERSION 3.23)
project(mikroprojekt3)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -Wpedantic")

include_directories(include)

add_subdirectory(src)