//
// Created by Roy on 08/12/2024.
//

#ifndef DAY9_H
#define DAY9_H
#include "base/solution.h"

namespace Day9 {

class Day9 final : Solution {

public:
    std::pair<std::string, long long> solutionA() override;
    std::pair<std::string, long long> solutionB() override;

private:
    std::string inputALocation = "../puzzles/day9/input.txt";
    std::string inputBLocation = "../puzzles/day9/input.txt";
};

} // Day9

#endif //DAY9_H
