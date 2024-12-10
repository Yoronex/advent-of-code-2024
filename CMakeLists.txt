cmake_minimum_required(VERSION 3.30)
project(advent_of_code_2024)
include_directories(puzzles)

set(CMAKE_CXX_STANDARD 11)

add_executable(advent_of_code_2024 main.cpp
        puzzles/base/Solution.h
        puzzles/base/Solution.cpp
        puzzles/day1/Day1.h
        puzzles/day1/Day1.cpp
        puzzles/day2/Day2.h
        puzzles/day2/Day2.cpp
        puzzles/day3/Day3.cpp
        puzzles/day3/Day3.h
        puzzles/day4/Day4.cpp
        puzzles/day4/Day4.h
        puzzles/day5/Day5.cpp
        puzzles/day5/Day5.h
        puzzles/day6/Day6.cpp
        puzzles/day6/Day6.h
        puzzles/day7/Day7.cpp
        puzzles/day7/Day7.h
        puzzles/day8/Day8.cpp
        puzzles/day8/Day8.h
        puzzles/day9/Day9.cpp
        puzzles/day9/Day9.h)
