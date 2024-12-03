//
// Created by Roy on 03/12/2024.
//

#ifndef DAY3_H
#define DAY3_H
#include <base/solution.h>


class Day3 final : public Solution {

public:
    std::pair<std::string, int> solutionA() override;
    std::pair<std::string, int> solutionB() override;

private:
    std::string inputALocation = "../puzzles/day3/input.txt";
    std::string inputBLocation = "../puzzles/day3/input.txt";
};



#endif //DAY3_H
