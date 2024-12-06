//
// Created by Roy on 06/12/2024.
//

#ifndef DAY6_H
#define DAY6_H
#include "base/solution.h"


class Day6 final : public Solution {
public:
    std::pair<std::string, int> solutionA() override;
    std::pair<std::string, int> solutionB() override;

private:
    std::string inputALocation = "../puzzles/day6/input.txt";
    std::string inputBLocation = "../puzzles/day6/input.txt";
};



#endif //DAY6_H
