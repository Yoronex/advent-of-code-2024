//
// Created by Roy on 16/12/2024.
//

#ifndef DAY16_H
#define DAY16_H
#include "base/solution.h"

namespace Day16 {

class Day16 final : public Solution {
public:
    std::pair<std::string, long long> solutionA() override;
    std::pair<std::string, long long> solutionB() override;

private:
    std::string inputALocation = "../puzzles/day16/input.txt";
    std::string inputBLocation = "../puzzles/day16/input.txt";
};

} // Day16

#endif //DAY16_H
