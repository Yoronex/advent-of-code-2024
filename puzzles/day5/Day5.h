//
// Created by Roy on 04/12/2024.
//

#ifndef DAY5_H
#define DAY5_H
#include "base/solution.h"


class Day5 final : public Solution {
public:
    std::pair<std::string, long long> solutionA() override;
    std::pair<std::string, long long> solutionB() override;

private:
    std::string inputALocation = "../puzzles/day5/input.txt";
    std::string inputBLocation = "../puzzles/day5/input.txt";
};



#endif //DAY5_H
