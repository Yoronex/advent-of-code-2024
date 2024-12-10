//
// Created by Roy on 10/12/2024.
//

#include "Day10.h"

#include <set>

namespace Day10 {
    bool isValidStep(const std::vector<std::string> &grid, long long currentHeight, const std::pair<long long, long long> &newPosition) {
        const long long gridWidth = grid[0].size();
        const long long gridHeight = grid.size();
        const long long x = newPosition.first;
        const long long y = newPosition.second;

        if (x < 0 || y < 0 || x >= gridWidth || y >= gridHeight) return false;

        const long long z = std::stoll(grid[y].substr(x, 1));
        return z == currentHeight + 1;
    }

    std::set<std::pair<long long, long long>> findHikingTrailFinishPoints(const std::vector<std::string> &grid, const std::pair<long long, long long> &currentPosition) {
        const long long x = currentPosition.first;
        const long long y = currentPosition.second;
        const long long z = std::stoll(grid[y].substr(x, 1));

        std::set<std::pair<long long, long long>> endPoints{};

        if (z == 9) {;
            endPoints.insert(currentPosition);
            return endPoints;
        }

        const std::set<std::pair<long long, long long>> newPositions{
            std::make_pair(x, y - 1),
            std::make_pair(x, y + 1),
            std::make_pair(x - 1, y),
            std::make_pair(x + 1, y),
        };

        for (auto newPosition : newPositions) {
            if (isValidStep(grid, z, newPosition)) {
                auto endpointsByStep = findHikingTrailFinishPoints(grid, newPosition);
                endPoints.insert(endpointsByStep.begin(), endpointsByStep.end());
            }
        }

        return endPoints;
    }

    std::pair<std::string, long long> Day10::solutionA() {
        const std::vector<std::string> input = readInput(inputALocation);
        const long long width = input[0].size();
        const long long height = input.size();

        std::set<std::pair<long long, long long>> startingPoints;
        for (long long y = 0; y < height; y++) {
            for (long long x = 0; x < width; x++) {
                if (input[y][x] == '0') {
                    startingPoints.insert(std::make_pair(x, y));
                }
            }
        }

        long long scoreSum = 0;
        for (const auto startingPoint : startingPoints) {
            auto endPoints = findHikingTrailFinishPoints(input, startingPoint);
            scoreSum += endPoints.size();
        }

        return std::make_pair("day 10a", scoreSum);
    }

    std::vector<std::pair<long long, long long>> findHikingTrailFinishPointsPaths(const std::vector<std::string> &grid, const std::pair<long long, long long> &currentPosition) {
        const long long x = currentPosition.first;
        const long long y = currentPosition.second;
        const long long z = std::stoll(grid[y].substr(x, 1));

        std::vector<std::pair<long long, long long>> endPoints{};

        if (z == 9) {;
            endPoints.push_back(currentPosition);
            return endPoints;
        }

        const std::set<std::pair<long long, long long>> newPositions{
            std::make_pair(x, y - 1),
            std::make_pair(x, y + 1),
            std::make_pair(x - 1, y),
            std::make_pair(x + 1, y),
        };

        for (auto newPosition : newPositions) {
            if (isValidStep(grid, z, newPosition)) {
                std::vector<std::pair<long long, long long>> endpointsByStep = findHikingTrailFinishPointsPaths(grid, newPosition);
                for (const auto &pair : endpointsByStep)
                    endPoints.emplace_back(pair);
            }
        }

        return endPoints;
    }

    std::pair<std::string, long long> Day10::solutionB() {
        const std::vector<std::string> input = readInput(inputBLocation);
        const long long width = input[0].size();
        const long long height = input.size();

        std::vector<std::pair<long long, long long>> startingPoints;
        for (long long x = 0; x < width; x++) {
            for (long long y = 0; y < height; y++) {
                if (input[y][x] == '0') {
                    startingPoints.emplace_back(x, y);
                }
            }
        }

        long long ratingSum = 0;
        for (const auto startingPoint : startingPoints) {
            auto endPoints = findHikingTrailFinishPointsPaths(input, startingPoint);
            ratingSum += endPoints.size();
        }

        return std::make_pair("day 10a", ratingSum);
    }

} // Day10