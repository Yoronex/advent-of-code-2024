//
// Created by Roy on 06/12/2024.
//

#ifndef DAY7_H
#define DAY7_H
#include "base/solution.h"

namespace Day7 {

    class Day7 final : public Solution {
    public:
        std::pair<std::string, long long> solutionA() override;
        std::pair<std::string, long long> solutionB() override;

    private:
        std::string inputALocation = "../puzzles/day7/input.txt";
        std::string inputBLocation = "../puzzles/day7/input.txt";
};

} // Day7

#endif //DAY7_H
