#include <iostream>

#include "day2/Day2.h"
#include "day3/Day3.h"
#include "day4/Day4.h"
#include "day5/Day5.h"

int main() {

    auto const solution = Day5().solutionB();
    std::cout << "Solution for " << solution.first << ": " << solution.second << std::endl;

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.