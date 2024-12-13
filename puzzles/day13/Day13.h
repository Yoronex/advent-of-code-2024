//
// Created by Roy on 13/12/2024.
//

#ifndef DAY13_H
#define DAY13_H
#include "base/solution.h"

namespace Day13 {

class Day13 final : public Solution {
public:
    std::pair<std::string, long long> solutionA() override;
    std::pair<std::string, long long> solutionB() override;

private:
    std::string inputALocation = "../puzzles/day13/input.txt";
    std::string inputBLocation = "../puzzles/day13/input.txt";
};

} // Day13

#endif //DAY13_H
