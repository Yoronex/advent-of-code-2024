//
// Created by Roy on 30/11/2024.
//

#ifndef DAY1_H
#define DAY1_H

#include <../puzzles/base/solution.h>

class Day1 final : public Solution {
public:
    std::pair<std::string, long long> solutionA() override;
    std::pair<std::string, long long> solutionB() override;

private:
    std::string inputALocation = "../puzzles/day1/input_a.txt";
    std::string inputBLocation = "../puzzles/day1/input_a.txt";
};



#endif //DAY1_H
