//
// Created by Roy on 11/12/2024.
//

#ifndef DAY11_H
#define DAY11_H
#include "base/solution.h"

namespace Day11 {

long long newAsteroidGroupSumDFS(const std::vector<std::string> &asteroids, int iterationsLeft);
long long countAsteroidsAfterIterationsDFS(const std::string &asteroid, int iterationsLeft);

class Day11 final : public Solution {
public:
    std::pair<std::string, long long> solutionA() override;
    std::pair<std::string, long long> solutionB() override;

private:
    std::string inputALocation = "../puzzles/day11/input.txt";
    std::string inputBLocation = "../puzzles/day11/input.txt";
};

} // Day11

#endif //DAY11_H
