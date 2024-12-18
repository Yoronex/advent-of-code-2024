//
// Created by Roy on 18/12/2024.
//

#include "Day18.h"

#include <iostream>
#include <map>
#include <set>

#include "base/Grid.h"

namespace Day18 {

    Position Day18::parseCoordinate(const std::string &row) const {
        const auto coordinates = split(row, ",");
        const int x = std::stoi(coordinates[0]);
        const int y = std::stoi(coordinates[1]);
        return {x, y};
    }

    Grid<std::string> Day18::parseInput(const std::vector<std::string> &input, const int gridSize, const int bytesToDrop) const {
        Grid<std::string> grid(gridSize, gridSize, ".");

        int i = 0;
        for (const auto &row : input) {
            if (i >= bytesToDrop) break;
            Position p = parseCoordinate(row);
            grid.set(p, "#");
            i++;
        }

        return grid;
    }

    // returns how many bytes were dropped
    int Day18::dropBytes(Grid<std::string> &grid, const std::vector<std::string> &input, const int start, const std::set<Position> &path) const {
        int i = start;
        int dropped = 0;

        while (i + dropped < input.size()) {
            const std::string row = input[i + dropped];
            Position p = parseCoordinate(row);
            grid.set(p, "#");
            dropped++;

            // We blocked the path
            if (path.find(p) != path.end()) break;
        }

        return dropped;
    }

    void printGrid(const Grid<std::string> &grid) {
        for (long long y = 0; y < grid.getHeight(); y++) {
            std::string row;
            for (long long x = 0; x < grid.getWidth(); x++) {
                row += grid.get({ x, y });
            }
            std::cout << row << std::endl;
        }
    }

    struct AStarPosition {
        Position pos;
        long long f;
        long long g;

        bool operator<(const AStarPosition &rhs) const {
            return this->pos < rhs.pos;
        }
    };

    long long estimatedCostsToEndpoint(const Position &currentPosition, const Position &goal) {
        const long long xDiff = currentPosition.x - goal.x;
        const long long yDiff = currentPosition.y - goal.y;

        // We are at the goal
        if (xDiff == 0 && yDiff == 0) return 0;
        const long long movementScore = std::abs(xDiff) + std::abs(yDiff);

        return movementScore;
    }

    std::vector<Position> findPath(const Grid<std::string> &maze) {
        Position startPoint{ -1, -1 };
        Position endPoint{ -1, -1 };

        for (long long y = 0; y < maze.getHeight(); y++) {
            for (long long x = 0; x < maze.getWidth(); x++) {
                if (maze.get({ x, y }) == "S") {
                    startPoint = {x, y};
                }
                if (maze.get({ x, y }) == "E") {
                    endPoint = { x, y };
                }
                if (startPoint.x >= 0 && endPoint.x >= 0) break;
            }
            if (startPoint.x >= 0 && endPoint.x >= 0) break;
        }

        const long long defaultF = estimatedCostsToEndpoint(startPoint, endPoint);

        std::set<AStarPosition> openSet{ { startPoint, defaultF, 1 } };
        std::set<AStarPosition> closedSet{};
        std::map<Position, Position> cameFrom;

        long long i = 0;

        while (!openSet.empty()) {
            AStarPosition q = *openSet.begin();
            for (const auto &possibleQ : openSet) {
                if (possibleQ.f < q.f) {
                    q = possibleQ;
                }
            }
            openSet.erase(q);
            closedSet.insert(q);

            if (q.pos == endPoint) {
                // Reconstruct
                Position p = endPoint;
                std::vector<Position> path{endPoint};

                while (p != startPoint) {
                    const auto match = cameFrom.find(p);
                    if (match == cameFrom.end()) {
                        break;
                    }
                    p = match->second;
                    path.push_back(p);
                }

                return path;
            }

            std::vector<Position> successors;
            Position p{q.pos.x, q.pos.y - 1};
            if (maze.has(p) && maze.get(p) != "#") {
                successors.push_back(p);
            }
            p = { q.pos.x, q.pos.y + 1 };
            if (maze.has(p) && maze.get(p) != "#") {
                successors.push_back(p);
            }
            p = {q.pos.x - 1, q.pos.y};
            if (maze.has(p) && maze.get(p) != "#") {
                successors.push_back(p);
            }
            p = {q.pos.x + 1, q.pos.y};
            if (maze.has(p) && maze.get(p) != "#") {
                successors.push_back(p);
            }

            for (const auto &successor : successors) {
                const long long g = q.g + 1;
                const long long h = estimatedCostsToEndpoint(successor, endPoint);
                const long long f = g + h;

                const auto matchOpen = openSet.find({ successor });
                if (matchOpen != openSet.end() && matchOpen->f < f) continue;
                const auto matchClosed = closedSet.find({ successor });
                if (matchClosed != closedSet.end() && matchClosed->f < f) continue;

                openSet.insert({ successor, f, g });
                cameFrom.insert(std::make_pair(successor, q.pos));
            }

            i++;

            if (i % 1000 == 0) {
                std::cout << i << std::endl;
            }
        }

        // Goal not found?
        return {};
    }

    std::pair<std::string, long long> Day18::solutionA() {
        const std::vector<std::string> input = readInput(inputALocation);
        const int gridSize = 71;
        Grid<std::string> grid = parseInput(input, gridSize, 1024);

        grid.set({0, 0}, "S");
        grid.set({gridSize - 1, gridSize - 1}, "E");

        const auto path = findPath(grid);
        for (const auto &step : path) {
            grid.set(step, "O");
        }

        return std::make_pair("day 18a", path.size() - 1);
    }

    std::pair<std::string, long long> Day18::solutionB() {
        const std::vector<std::string> input = readInput(inputALocation);
        const int gridSize = 71;
        int bytesDropped = 1024;
        Grid<std::string> grid = parseInput(input, gridSize, bytesDropped);
        grid.set({0, 0}, "S");
        grid.set({gridSize - 1, gridSize - 1}, "E");
        printGrid(grid);

        auto path = findPath(grid);
        while (!path.empty()) {
            std::cout << "Path of size " << path.size() << std::endl;
            const std::set<Position> pathSet{path.begin(), path.end()};
            bytesDropped += dropBytes(grid, input, bytesDropped, pathSet);
            path = findPath(grid);
        }

        std::cout << "Last coordinate: " << input[bytesDropped - 1] << " (index: " << bytesDropped - 1 << ")" << std::endl;

        return std::make_pair("day 18b", 0);
    }

} // Day18