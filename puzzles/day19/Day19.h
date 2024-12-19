//
// Created by Roy on 19/12/2024.
//

#ifndef DAY19_H
#define DAY19_H
#include "base/solution.h"

namespace Day19 {

    class Day19 final : public Solution {
    public:
        std::pair<std::string, long long> solutionA() override;
        std::pair<std::string, long long> solutionB() override;

    private:
        std::string inputALocation = "../puzzles/day19/input.txt";
        std::string inputBLocation = "../puzzles/day19/input.txt";
    };

} // Day19

#endif //DAY19_H
