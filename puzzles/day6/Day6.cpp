//
// Created by Roy on 06/12/2024.
//

#include "Day6.h"

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

enum class Day6MoveDirection {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

struct Day6Position {
    Day6MoveDirection direction;
    int x;
    int y;
};

bool operator<(const Day6Position &lhs, const Day6Position &rhs) {
    if (lhs.direction < rhs.direction) return true;
    if (lhs.direction > rhs.direction) return false;
    if (lhs.x < rhs.x) return true;
    if (lhs.x > rhs.x) return false;
    if (lhs.y < rhs.y) return true;
    if (lhs.y > rhs.y) return false;
    return false;
}

Day6MoveDirection day6nextDirection(const Day6MoveDirection &dir) {
    switch (dir) {
        case Day6MoveDirection::UP: return Day6MoveDirection::RIGHT;
        case Day6MoveDirection::RIGHT: return Day6MoveDirection::DOWN;
        case Day6MoveDirection::DOWN: return Day6MoveDirection::LEFT;
        case Day6MoveDirection::LEFT: return Day6MoveDirection::UP;
    }
    // Shouldn't be here!
    throw;
}

std::string day6GetLineOfSight(const std::vector<std::string> &grid, const Day6Position &pos) {
    std::string result;
    switch (pos.direction) {
        case Day6MoveDirection::UP: for (int y = pos.y - 1; y >= 0; y--) result += grid[y][pos.x]; break;
        case Day6MoveDirection::DOWN: for (int y = pos.y + 1; y < grid.size(); y++) result += grid[y][pos.x]; break;
        case Day6MoveDirection::LEFT: {
            result = grid[pos.y].substr(0, pos.x);
            std::reverse(result.begin(), result.end());
            break;
        }
        case Day6MoveDirection::RIGHT: {
            result = grid[pos.y].substr(pos.x + 1, grid[pos.y].size() - pos.x);
            break;
        }
    }
    return result;
}

std::pair<Day6MoveDirection, std::vector<std::string>> day6CreateNewPosition(const std::vector<std::string> &currentGrid) {
    int x;
    int y;
    Day6MoveDirection direction;

    std::vector<std::string> newGrid = currentGrid;

    for (int i = 0; i < currentGrid.size(); i++) {
        for (int j = 0; j < currentGrid[0].size(); j++) {
            if (currentGrid[i][j] != '.' && currentGrid[i][j] != '#') {
                x = j;
                y = i;
                newGrid[i][j] = '.';
            }
            if (currentGrid[i][j] == '^') {
                direction = Day6MoveDirection::UP;
                if (i > 0 && currentGrid[i - 1][j] != '#') {
                    newGrid[i - 1][j] = '^';
                } else if (i > 0 && currentGrid[i - 1][j] == '#') {
                    newGrid[i][j + 1] = '>';
                    direction = day6nextDirection(direction);
                }
            } else if (currentGrid[i][j] == '>') {
                direction = Day6MoveDirection::RIGHT;
                if (j < currentGrid[0].size() - 1 && currentGrid[i][j + 1] != '#') {
                    newGrid[i][j + 1] = '>';
                } else if (j < currentGrid[0].size() - 1 && currentGrid[i][j + 1] == '#') {
                    newGrid[i + 1][j] = 'v';
                    direction = day6nextDirection(direction);
                }
            } else if (currentGrid[i][j] == 'v') {
                direction = Day6MoveDirection::DOWN;
                if (i < currentGrid.size() - 1 && currentGrid[i + 1][j] != '#') {
                    newGrid[i + 1][j] = 'v';
                } else if (i < currentGrid.size() - 1 && currentGrid[i + 1][j] == '#') {
                    newGrid[i][j - 1] = '<';
                    direction = day6nextDirection(direction);
                }
            } else if (currentGrid[i][j] == '<') {
                direction = Day6MoveDirection::LEFT;
                if (j > 0 && currentGrid[i][j - 1] != '#') {
                    newGrid[i][j - 1] = '<';
                } else if (j > 0 && currentGrid[i][j - 1] == '#') {
                    newGrid[i - 1][j] = '^';
                    direction = day6nextDirection(direction);
                }
            }
        }
    }

    return std::make_pair(direction, newGrid);
}

int day6GetDistanceToMove(const std::vector<std::string> &grid, const Day6Position &pos) {
    std::string lineOfSight = day6GetLineOfSight(grid, pos);
    int distanceToBlock = lineOfSight.find('#');
    if (distanceToBlock == std::string::npos) {
        return INT_MAX;
    } else {
        return distanceToBlock;
    }
}

void day6CreateNewPositionToBlock(std::vector<std::string> &grid) {
    Day6MoveDirection direction;
    std::string lineOfSight;
    int distanceToBlock;

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[0].size(); x++) {
            if (grid[y][x] == '^') {
                direction = Day6MoveDirection::UP;
                distanceToBlock = day6GetDistanceToMove(grid, { direction, x, y });
                if (distanceToBlock != INT_MAX) {
                    grid[y - distanceToBlock][x] = '>';
                }
                if (distanceToBlock > 0) {
                    grid[y][x] = '.';
                }
            } else if (grid[y][x] == '>') {
                direction = Day6MoveDirection::RIGHT;
                distanceToBlock = day6GetDistanceToMove(grid, { direction, x, y });
                if (distanceToBlock != INT_MAX) {
                    grid[y][x + distanceToBlock] = 'v';
                }
                if (distanceToBlock > 0) {
                    grid[y][x] = '.';
                }
            } else if (grid[y][x] == 'v') {
                direction = Day6MoveDirection::DOWN;
                distanceToBlock = day6GetDistanceToMove(grid, { direction, x, y });
                if (distanceToBlock != INT_MAX) {
                    grid[y + distanceToBlock][x] = '<';
                }
                if (distanceToBlock > 0) {
                    grid[y][x] = '.';
                }
            } else if (grid[y][x] == '<') {
                direction = Day6MoveDirection::LEFT;
                distanceToBlock = day6GetDistanceToMove(grid, { direction, x, y });
                if (distanceToBlock != INT_MAX) {
                    grid[y][x - distanceToBlock] = '^';
                }
                if (distanceToBlock > 0) {
                    grid[y][x] = '.';
                }
            }
            // if (grid[y][x] != '.' && grid[y][x] != '#') {
            //     grid[y][x] = '.';
            //     return;
            // }
        }
    }
}

bool day6InLineOfLoop(const std::vector<std::string> &grid, const std::set<Day6Position> &positions, const Day6Position &currentPosition) {
    // std::set<Day6Position> positionsInLine;
    std::string lineOfSight = day6GetLineOfSight(grid, currentPosition);
    // std::transform(positions.begin(), positions.end(), positionsInLine.insert, [currentPosition, lineOfSight](const Day6Position &pos) -> bool {
    for (const Day6Position &pos : positions) {
        if (pos.direction != currentPosition.direction) continue;

        int distance = -1;
        switch (pos.direction) {
            case Day6MoveDirection::UP: {
                if (pos.x != currentPosition.x) continue;
                if (pos.y >= currentPosition.y) continue;
                distance = currentPosition.y - pos.y;
                break;
            }
            case Day6MoveDirection::DOWN: {
                if (pos.x != currentPosition.x) continue;
                if (pos.y <= currentPosition.y) continue;
                distance = pos.y - currentPosition.y;
                break;
            }
            case Day6MoveDirection::LEFT: {
                if (pos.y != currentPosition.y) continue;
                if (pos.x >= currentPosition.x) continue;
                distance = currentPosition.x - pos.x;
                break;
            }
            case Day6MoveDirection::RIGHT: {
                if (pos.y != currentPosition.y) continue;
                if (pos.x <= currentPosition.x) continue;
                distance = pos.x - currentPosition.x;
                break;
            }
        }
        const std::string substr = lineOfSight.substr(0, distance);
        if (substr.find('#') == std::string::npos) return true;
    }
    return false;
}

Day6Position day6GetPosition(const std::vector<std::string> &grid) {
    int x = -1;
    int y = -1;
    auto direction = Day6MoveDirection::UP;

    for (int i = 0; i < grid.size(); i++) {
        if (x >= 0 && y >= 0) break;
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] != '.' && grid[i][j] != '#') {
                x = j;
                y = i;
                switch (grid[i][j]) {
                    case '^': direction = Day6MoveDirection::UP; break;
                    case 'v': direction = Day6MoveDirection::DOWN; break;
                    case '<': direction = Day6MoveDirection::LEFT; break;
                    case '>': direction = Day6MoveDirection::RIGHT; break;
                }
                break;
            }
        }
    }

    return { direction, x, y };
}

void day6ApplyPositionToGrid(std::vector<std::string> &grid, const Day6Position &pos) {
    switch (pos.direction) {
        case Day6MoveDirection::UP: grid[pos.y][pos.x] = '^'; break;
        case Day6MoveDirection::DOWN: grid[pos.y][pos.x] = 'v'; break;
        case Day6MoveDirection::LEFT: grid[pos.y][pos.x] = '>'; break;
        case Day6MoveDirection::RIGHT: grid[pos.y][pos.x] = '<'; break;
    }
}

void day6PrintGrid(const std::vector<std::string> &grid) {
    for (const auto &row : grid) {
        std::cout << row << std::endl;
    }
    std::cout << std::endl;
}

std::set<std::pair<int, int>> day6GetPositions(const std::vector<std::string> &input) {
    std::vector<std::string> grid = input;
    std::set<std::pair<int, int>> positions;

    Day6Position currentPosition = day6GetPosition(grid);
    while (currentPosition.x >= 0 || currentPosition.y >= 0) {
        currentPosition = day6GetPosition(grid);
        if (currentPosition.x >= 0 && currentPosition.y >= 0) {
            positions.insert(std::make_pair(currentPosition.x, currentPosition.y));
        }
        grid = day6CreateNewPosition(grid).second;

        // day6PrintGrid(input);
    }

    return positions;
}

std::pair<std::string, long long> Day6::solutionA() {
    std::vector<std::string> input = readInput(inputALocation);
    // day6PrintGrid(input);

    std::set<std::pair<int, int>> positions = day6GetPositions(input);

    for (const auto &position : positions) {
        input[position.second][position.first] = 'X';
    }

    // day6PrintGrid(input);

    return std::make_pair("day 6a", positions.size());
}

bool day6IsLooping(std::vector<std::string> &grid) {
    std::set<Day6Position> positions;

    Day6Position currentPosition = day6GetPosition(grid);
    while (currentPosition.x >= 0 || currentPosition.y >= 0) {
        currentPosition = day6GetPosition(grid);
        if (currentPosition.x < 0 || currentPosition.y < 0) return false;
        if (positions.find(currentPosition) != positions.end()) return true;

        positions.insert(currentPosition);
        // grid = day6CreateNewPosition(grid).second;
        day6CreateNewPositionToBlock(grid);
    }

    return false;
}

std::pair<std::string, long long> Day6::solutionB() {
    const std::vector<std::string> input = readInput(inputALocation);
    std::vector<std::string> grid = input;

    std::set<std::pair<int, int>> obstaclesCausingLoops;

    std::set<std::pair<int, int>> positions = day6GetPositions(input);
    Day6Position initialPosition = day6GetPosition(grid);
    positions.erase({ initialPosition.x, initialPosition.y });

    int i = 0;
    for (const auto &newObstacle : positions) {
        if (input[newObstacle.second][newObstacle.first] != '#' && obstaclesCausingLoops.find(newObstacle) == obstaclesCausingLoops.end()) {
            std::vector<std::string> newGrid = input;
            // day6ApplyPositionToGrid(newGrid, currentPosition);
            newGrid[newObstacle.second][newObstacle.first] = '#';
            if (day6IsLooping(newGrid)) {
                newGrid[newObstacle.second][newObstacle.first] = 'O';
                // day6PrintGrid(newGrid);
                obstaclesCausingLoops.insert(newObstacle);
            }
        }

        grid = day6CreateNewPosition(grid).second;

        i++;
        std::cout << i << std::endl;
    }

    return std::make_pair("day 6a", obstaclesCausingLoops.size());
}
