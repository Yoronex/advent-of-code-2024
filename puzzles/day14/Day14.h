//
// Created by Roy on 14/12/2024.
//

#ifndef DAY14_H
#define DAY14_H
#include "base/solution.h"

namespace Day14 {


class Day14 final : public Solution {
public:
    std::pair<std::string, long long> solutionA() override;
    std::pair<std::string, long long> solutionB() override;

private:
    std::string inputALocation = "../puzzles/day14/input.txt";
    std::string inputBLocation = "../puzzles/day14/input.txt";
};

} // Day14

#endif //DAY14_H
