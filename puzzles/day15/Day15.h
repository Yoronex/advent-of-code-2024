//
// Created by Roy on 14/12/2024.
//

#ifndef DAY15_H
#define DAY15_H
#include "base/solution.h"

namespace Day15 {

class Day15 final : public Solution {
public:
    std::pair<std::string, long long> solutionA() override;
    std::pair<std::string, long long> solutionB() override;

private:
    std::string inputALocation = "../puzzles/day15/input.txt";
    std::string inputBLocation = "../puzzles/day15/input.txt";
};

} // Day15

#endif //DAY15_H
