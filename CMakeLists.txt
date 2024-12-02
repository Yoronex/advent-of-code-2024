cmake_minimum_required(VERSION 3.30)
project(advent_of_code_2024)
include_directories(puzzles)

set(CMAKE_CXX_STANDARD 11)

add_executable(advent_of_code_2024 main.cpp puzzles/base/Solution.cpp puzzles/day1/Day1.cpp puzzles/day2/Day2.cpp)
