//
// Created by Roy on 14/12/2024.
//

#include "Day14.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <set>

namespace Day14 {
    struct Robot {
        Position initialPosition;
        Position velocity;
    };

    long long positiveModulo(long long n, long long mod) {
        return ((n % mod) + mod) % mod;
    }

    Position getRobotPositionAfterTime(const Robot &robot, const long long seconds, const long long gridWidth, const long long gridHeight) {
        const long long finalX = positiveModulo((robot.velocity.x * seconds) + robot.initialPosition.x, gridWidth);
        const long long finalY = positiveModulo((robot.velocity.y * seconds) + robot.initialPosition.y, gridHeight);
        return {finalX, finalY};
    }

    int getPositionQuadrant(const Position &position, const long long gridWidth, const long long gridHeight) {
        const long long xBorder = gridWidth / 2;
        const long long yBorder = gridHeight / 2;
        if (position.x < xBorder && position.y < yBorder) return 0;
        if (position.x > xBorder && position.y < yBorder) return 1;
        if (position.x < xBorder && position.y > yBorder) return 2;
        if (position.x > xBorder && position.y > yBorder) return 3;
        return -1;
    }

    void printRobotsInGrid(const std::vector<Position> &robotPositions, const long long gridWidth, const long long gridHeight) {
        Grid<int> grid(gridWidth, gridHeight, 0);
        for (const auto &pos : robotPositions) {
            const int currentCount = grid.get(pos);
            grid.set(pos, currentCount + 1);
        }

        for (long long y = 0; y < grid.getHeight(); y++) {
            std::string line = "";
            for (long long x = 0; x < grid.getWidth(); x++) {
                const int count = grid.get({x, y});
                if (count <= 0) {
                    line += ".";
                } else {
                    line += std::to_string(count).substr(0, 1);
                }
            }
            std::cout << line << std::endl;
        }
    }

    std::pair<std::string, long long> Day14::solutionA() {
        const std::vector<std::string> input = readInput(inputALocation);
        constexpr long long gridWidth = 101;
        constexpr long long gridHeight = 103;

        std::vector<Robot> robots;
        robots.reserve(input.size());
        for (const auto &row : input) {
            const auto temp1 = split(row, " v=");
            const auto rawPosition = split(split(temp1[0], "p=")[1], ",");
            const auto rawVelocity = split(temp1[1], ",");
            Robot robot = {
                {
                   std::stoll(rawPosition[0]),
                   std::stoll(rawPosition[1]),
                }, {
                    std::stoll(rawVelocity[0]),
                    std::stoll(rawVelocity[1]),
                }};
            robots.push_back(robot);
        }

        std::vector<Position> finalPositions;
        for (const auto &robot : robots) {
            Position finalPosition = getRobotPositionAfterTime(robot, 100, gridWidth, gridHeight);
            finalPositions.push_back(finalPosition);
        }

        std::array<long long, 4> quadrantCounts{0, 0, 0, 0};
        for (const auto &finalPosition : finalPositions) {
            const int quadrant = getPositionQuadrant(finalPosition, gridWidth, gridHeight);
            if (quadrant < 0) continue;
            quadrantCounts[quadrant]++;
        }

        long long sum = 1;
        for (const auto quadrant : quadrantCounts) {
            sum *= quadrant;
        }

        return std::make_pair<std::string, long long>("day 14a", std::move(sum));
    }

    std::pair<std::string, long long> Day14::solutionB() {
        const std::vector<std::string> input = readInput(inputBLocation);
        constexpr long long gridWidth = 101;
        constexpr long long gridHeight = 103;
        constexpr long long maxSeconds = 100000;

        std::vector<Robot> robots;
        robots.reserve(input.size());
        for (const auto &row : input) {
            const auto temp1 = split(row, " v=");
            const auto rawPosition = split(split(temp1[0], "p=")[1], ",");
            const auto rawVelocity = split(temp1[1], ",");
            Robot robot = {
                {
                    std::stoll(rawPosition[0]),
                    std::stoll(rawPosition[1]),
                 }, {
                     std::stoll(rawVelocity[0]),
                     std::stoll(rawVelocity[1]),
                 }};
            robots.push_back(robot);
        }

        for (long long second = 0; second < maxSeconds; second++) {
            std::vector<Position> finalPositions;
            for (const auto &robot : robots) {
                Position finalPosition = getRobotPositionAfterTime(robot, second, gridWidth, gridHeight);
                finalPositions.push_back(finalPosition);
            }

            std::set<Position> finalPositionsSet(finalPositions.begin(), finalPositions.end());

            if (finalPositions.size() == finalPositionsSet.size()) {
                printRobotsInGrid(finalPositions, gridWidth, gridHeight);
                std::cout << "After " << second << " seconds" << std::endl << std::endl;
            }
        }

        return std::make_pair<std::string, long long>("day 14b", 0);
    }


} // Day14