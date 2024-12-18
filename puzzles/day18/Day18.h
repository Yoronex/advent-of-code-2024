//
// Created by Roy on 18/12/2024.
//

#ifndef DAY18_H
#define DAY18_H
#include <set>

#include "base/Grid.h"
#include "base/solution.h"

namespace Day18 {

    class Day18 final : public Solution {
    public:
        std::pair<std::string, long long> solutionA() override;
        std::pair<std::string, long long> solutionB() override;

    private:
        std::string inputALocation = "../puzzles/day18/input.txt";
        std::string inputBLocation = "../puzzles/day18/input.txt";

        Position parseCoordinate(const std::string &row) const;
        Grid<std::string> parseInput(const std::vector<std::string> &input, int gridSize, int bytesToDrop) const;
        int dropBytes(Grid<std::string> &grid, const std::vector<std::string> &input, int start, const std::set<Position> &path) const;
    };

} // Day18

#endif //DAY18_H
