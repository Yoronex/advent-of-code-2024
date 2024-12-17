//
// Created by Roy on 16/12/2024.
//

#include "Day16.h"

#include <iostream>
#include <map>
#include <set>

#include "base/Grid.h"

namespace Day16 {
    enum Direction {
        UP = 0,
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3,
    };

    struct PositionWDirection : public Position {
        Direction direction;

        bool operator<(const PositionWDirection &rhs) const {
            if (this->direction < rhs.direction) return true;
            if (this->direction > rhs.direction) return false;
            const Position lhsp = {this->x, this->y};
            const Position rhsp = {rhs.x, rhs.y};
            return lhsp < rhsp;
        }

        bool operator>(const PositionWDirection &rhs) const {
            return rhs < *this;
        }

        bool operator==(const PositionWDirection &rhs) const {
            return !(*this < rhs) && !(*this > rhs);
        }

        bool operator==(const Position &rhs) const {
            return this->x == rhs.x && this->y == rhs.y;
        }
    };

    bool operator==(const Position &lhs, const PositionWDirection &rhs) {
        return lhs.x == rhs.x && lhs.y && rhs.y;
    }

    long long getRotationScore(const Direction currentDirection, const Direction newDirection) {
        const auto rotationDiff = (newDirection - currentDirection + 4) % 4;
        const int rotationBase = std::min(rotationDiff, 4 - rotationDiff);
        return rotationBase * 1000;
    }

    long long estimatedCostsToEndpoint(const PositionWDirection &currentPosition, const Position &goal) {
        const long long xDiff = currentPosition.x - goal.x;
        const long long yDiff = currentPosition.y - goal.y;

        // We are at the goal
        if (xDiff == 0 && yDiff == 0) return 0;

        long long movementScore = std::abs(xDiff) + std::abs(yDiff);
        std::vector<Direction> relativeDirections;
        if (yDiff < 0) relativeDirections.push_back(Direction::DOWN);
        if (yDiff > 0) relativeDirections.push_back(Direction::UP);
        if (xDiff < 0) relativeDirections.push_back(Direction::RIGHT);
        if (xDiff > 0) relativeDirections.push_back(Direction::LEFT);

        long long rotationScore = 0;
        if (relativeDirections.size() == 1) {
            rotationScore = getRotationScore(currentPosition.direction, relativeDirections[0]);
        } else if (relativeDirections.size() > 1) {
            const auto match = std::find(relativeDirections.begin(), relativeDirections.end(), currentPosition.direction);
            if (match != relativeDirections.end()) {
                relativeDirections.erase(match);
            }
            rotationScore = relativeDirections.size() * 1000;
        }

        return movementScore + rotationScore;
    }

    struct AStarPosition {
        PositionWDirection pos;
        long long f;
        long long g;

        bool operator<(const AStarPosition &rhs) const {
            return this->pos < rhs.pos;
        }
    };

    long long findPath(const Grid<std::string> &maze) {
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

        PositionWDirection p1;
        p1.x = startPoint.x;
        p1.y = startPoint.y;
        p1.direction = Direction::UP;
        PositionWDirection p2;
        p2.x = startPoint.x;
        p2.y = startPoint.y;
        p2.direction = Direction::RIGHT;
        const long long defaultF = estimatedCostsToEndpoint(p1, endPoint);
        const long long defaultG = 0;

        std::set<AStarPosition> openSet{ { p1, defaultF, defaultG }, { p2, defaultF, defaultG } };
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

            if (q.pos == endPoint) {
                // Reconstruct
                return q.g;
            }

            std::vector<PositionWDirection> successors;
            if (maze.get({ q.pos.x, q.pos.y - 1 }) != "#") {
                PositionWDirection p;
                p.x = q.pos.x;
                p.y = q.pos.y - 1;
                p.direction = Direction::UP;
                successors.push_back(p);
            }
            if (maze.get({ q.pos.x, q.pos.y + 1 }) != "#") {
                PositionWDirection p;
                p.x = q.pos.x;
                p.y = q.pos.y + 1;
                p.direction = Direction::DOWN;
                successors.push_back(p);
            }
            if (maze.get({ q.pos.x - 1, q.pos.y }) != "#") {
                PositionWDirection p;
                p.x = q.pos.x - 1;
                p.y = q.pos.y;
                p.direction = Direction::LEFT;
                successors.push_back(p);
            }
            if (maze.get({ q.pos.x + 1, q.pos.y }) != "#") {
                PositionWDirection p;
                p.x = q.pos.x + 1;
                p.y = q.pos.y;
                p.direction = Direction::RIGHT;
                successors.push_back(p);
            }

            for (const auto &successor : successors) {
                const long long rotationScore = getRotationScore(q.pos.direction, successor.direction);
                const long long g = q.g + 1 + rotationScore;
                const long long h = estimatedCostsToEndpoint(successor, endPoint);
                const long long f = g + h;

                const auto match = openSet.find({ successor });
                if (match != openSet.end() && match->f < f) continue;
                openSet.insert({ successor, f, g });
                cameFrom.insert(std::make_pair(successor, q.pos));
            }

            i++;

            if (i % 1000 == 0) {
                std::cout << i << std::endl;
            }
        }

        // Goal not found?
        return LONG_LONG_MAX;
    }

    std::pair<std::string, long long> Day16::solutionA() {
        const std::vector<std::string> input = readInput(inputALocation);

        const Grid<std::string> maze(input);

        const long long score = findPath(maze);

        return std::make_pair("day 16a", score + 1000);
    }

    std::pair<std::string, long long> Day16::solutionB() {
        const std::vector<std::string> input = readInput(inputBLocation);
        return std::make_pair("day 16b", 0);
    }

} // Day16