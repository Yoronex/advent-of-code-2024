//
// Created by Roy on 07/12/2024.
//

#ifndef DAY8_H
#define DAY8_H
#include <string>

#include "base/solution.h"

namespace Day8 {

    class Day8 final: public Solution {
    public:
        std::pair<std::string, long long> solutionA() override;
        std::pair<std::string, long long> solutionB() override;

    private:
        std::string inputALocation = "../puzzles/day8/input.txt";
        std::string inputBLocation = "../puzzles/day8/input.txt";
};

} // Day8

#endif //DAY8_H
