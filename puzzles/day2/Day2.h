//
// Created by Roy on 30/11/2024.
//

#ifndef DAY2_H
#define DAY2_H

#include <../puzzles/base/solution.h>

class Day2 final : public Solution {
public:
    std::pair<std::string, int> solutionA() override;
    std::pair<std::string, int> solutionB() override;

    bool solution_isSafe(const std::vector<int> &row);

private:
    std::string inputALocation = "../puzzles/day2/input.txt";
    std::string inputBLocation = "../puzzles/day2/input.txt";
};



#endif //DAY2_H
