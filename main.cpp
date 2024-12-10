#include <chrono>
#include <iostream>

#include "day10/Day10.h"
#include "day2/Day2.h"
#include "day3/Day3.h"
#include "day4/Day4.h"
#include "day5/Day5.h"
#include "day6/Day6.h"
#include "day7/Day7.h"
#include "day8/Day8.h"
#include "day9/Day9.h"

int main() {

    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    auto startTime = now.time_since_epoch();

    auto const solution = Day10::Day10().solutionB();

    now = std::chrono::system_clock::now();
    auto finishTime = now.time_since_epoch();

    auto duration = finishTime - startTime;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    duration -= seconds;
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    duration -= milliseconds;
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration);

    std::cout << "Solution for " << solution.first << ": " << solution.second
        << " (" << seconds.count() << milliseconds.count() << "." << microseconds.count() << "ms)" << std::endl;

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.