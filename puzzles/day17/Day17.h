//
// Created by Roy on 17/12/2024.
//

#ifndef DAY17_H
#define DAY17_H
#include "base/solution.h"

namespace Day17 {

    class Day17 final : public Solution {
    public:
        std::pair<std::string, long long> solutionA() override;
        std::pair<std::string, long long> solutionB() override;

    private:
        std::string inputALocation = "../puzzles/day17/input.txt";
        std::string inputBLocation = "../puzzles/day17/input.txt";
    };

} // Day17

#endif //DAY17_H
