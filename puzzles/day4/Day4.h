//
// Created by Roy on 03/12/2024.
//

#ifndef DAY4_H
#define DAY4_H
#include <base/solution.h>


class Day4 final : public Solution {
public:
    std::pair<std::string, int> solutionA() override;
    std::pair<std::string, int> solutionB() override;

private:
    std::string inputALocation = "../puzzles/day4/input.txt";
    std::string inputBLocation = "../puzzles/day4/input.txt";
};



#endif //DAY4_H
