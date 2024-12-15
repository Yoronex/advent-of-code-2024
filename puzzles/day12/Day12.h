//
// Created by Roy on 11/12/2024.
//

#ifndef DAY12_H
#define DAY12_H
#include "base/solution.h"

namespace Day12 {

class Day12 final : public Solution {
public:
    std::pair<std::string, long long> solutionA() override;
    std::pair<std::string, long long> solutionB() override;

private:
    std::string inputALocation = "../puzzles/day12/input.txt";
    std::string inputBLocation = "../puzzles/day12/input.txt";
};

} // Day12

#endif //DAY12_H
