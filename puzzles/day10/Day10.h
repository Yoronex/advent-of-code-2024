//
// Created by Roy on 10/12/2024.
//

#ifndef DAY10_H
#define DAY10_H
#include "base/solution.h"

namespace Day10 {

class Day10 final : public Solution {
public:
    std::pair<std::string, long long> solutionA() override;
    std::pair<std::string, long long> solutionB() override;

private:
    std::string inputALocation = "../puzzles/day10/input.txt";
    std::string inputBLocation = "../puzzles/day10/input.txt";
};

} // Day10

#endif //DAY10_H
