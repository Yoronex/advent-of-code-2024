//
// Created by Roy on 11/12/2024.
//

#include "Day12.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <set>

#include "base/Grid.h"

namespace Day12 {
    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };

    Grid<int> setSameRegions(Grid<int> &grid, const std::vector<std::pair<int, int>> sameRegions) {
        std::vector<std::set<int>> sameRegionSets;
        for (const auto &r : sameRegions) {
            bool match = false;
            for (auto &set : sameRegionSets) {
                if (set.find(r.first) != set.end() || set.find(r.second) != set.end()) {
                    match = true;
                    set.insert(r.first);
                    set.insert(r.second);
                    break;
                }
            }
            if (!match) {
                sameRegionSets.push_back({r.first, r.second});
            }
        }

        for (int y = 0; y < grid.getHeight(); y++) {
            for (int x = 0; x < grid.getWidth(); x++) {
                Position p = {x, y};
                for (const std::set<int> &r : sameRegionSets) {
                    const auto match = r.find(grid.get(p));
                    // const auto match = std::find(r.begin(), r.end(), grid.get(p));
                    if (match != r.end()) {
                        grid.set(p, *r.begin());
                    }
                }
            }
        }

        return grid;
    }

    int getArea(const Grid<int> &grid, const int regionID) {
        int count = 0;
        for (int x = 0; x < grid.getWidth(); x++) {
            for (int y = 0; y < grid.getHeight(); y++) {
                if (grid.get({x, y}) == regionID) {
                    count++;
                }
            }
        }
        return count;
    }

    std::set<int> getRegionsWithinRegions(const Grid<int> &grid, const int regionID) {
        std::set<int> containedRegions;
        for (int y = 1; y < grid.getHeight() - 1; y++) {
            for (int x = 1; x < grid.getWidth() - 1; x++) {
                Position p = {x, y};
                if (containedRegions.find(grid.get(p)) != containedRegions.end()) continue;
                if (grid.get(p) == regionID) continue;

                const auto left = grid.left(p);
                const auto right = grid.right(p);
                const auto up = grid.up(p);
                const auto down = grid.down(p);
                bool contained = true;
                for (const std::vector<int> &side : {up, down, left, right}) {
                    if (std::find(side.begin(), side.end(), regionID) == side.end()) {
                        contained = false;
                        break;
                    }
                }
                if (contained) {
                    containedRegions.insert(grid.get(p));
                }
            }
        }

        return containedRegions;
    }

    int getPerimeter(const Grid<int> &grid, const int regionID) {
        Position startPoint {-1, -1};
        for (int y = 0; y < grid.getHeight(); y++) {
            if (startPoint.x != -1) break;
            for (int x = 0; x < grid.getWidth(); x++) {
                if (grid.get({x, y}) == regionID) {
                    startPoint = {x, y - 1};
                    break;
                }
            }
        }

        Position currentPos = startPoint;
        // Where the current region is
        Direction direction = Direction::DOWN;
        int perimeter = 0;
        do {
            switch (direction) {
                case Direction::UP: {
                    Position p = {currentPos.x, currentPos.y - 1};
                    if (grid.has(p) && grid.get(p) == regionID) {
                        perimeter++;

                        if (grid.has({currentPos.x - 1, currentPos.y}) && grid.get({currentPos.x - 1, currentPos.y}) == regionID) {
                            direction = Direction::LEFT;
                        } else {
                            currentPos = {currentPos.x - 1, currentPos.y};
                        }
                    } else {
                        currentPos = {currentPos.x, currentPos.y - 1};
                        direction = Direction::RIGHT;
                    }
                    break;
                }
                case Direction::DOWN: {
                    Position p = {currentPos.x, currentPos.y + 1};
                    if (grid.has(p) && grid.get(p) == regionID) {
                        perimeter++;
                        if (grid.has({currentPos.x + 1, currentPos.y}) && grid.get({currentPos.x + 1, currentPos.y}) == regionID) {
                            direction = Direction::RIGHT;
                        } else {
                            currentPos = {currentPos.x + 1, currentPos.y};
                        }
                    } else {
                        currentPos = {currentPos.x, currentPos.y + 1};
                        direction = Direction::LEFT;
                    }
                    break;
                }
                case Direction::LEFT: {
                    Position p = {currentPos.x - 1, currentPos.y};
                    if (grid.has(p) && grid.get(p) == regionID) {
                        perimeter++;
                        if (grid.has({currentPos.x, currentPos.y + 1}) && grid.get({currentPos.x, currentPos.y + 1}) == regionID) {
                            direction = Direction::DOWN;
                        } else {
                            currentPos = {currentPos.x, currentPos.y + 1};
                        }
                    } else {
                        currentPos = {currentPos.x - 1, currentPos.y};
                        direction = Direction::UP;
                    }
                    break;
                }
                case Direction::RIGHT: {
                    Position p = {currentPos.x + 1, currentPos.y};
                    if (grid.has(p) && grid.get(p) == regionID) {
                        perimeter++;
                        if (grid.has({currentPos.x, currentPos.y - 1}) && grid.get({currentPos.x, currentPos.y - 1}) == regionID) {
                            direction = Direction::UP;
                        } else {
                            currentPos = {currentPos.x, currentPos.y - 1};
                        }
                    } else {
                        currentPos = {currentPos.x + 1, currentPos.y};
                        direction = Direction::DOWN;
                    }
                    break;
                }
            }
        } while (currentPos != startPoint);

        const std::set<int> containedRegions = getRegionsWithinRegions(grid, regionID);
        for (const auto r : containedRegions) {
            perimeter += getPerimeter(grid, r);
        }

        return perimeter;
    }

    std::pair<std::string, long long> Day12::solutionA() {
        const std::vector<std::string> input = readInput(inputALocation);
        const Grid<std::string> inputGrid(input);

        std::vector<std::vector<int>> regionGridInput;
        regionGridInput.reserve(inputGrid.getHeight());
        for (int y = 0; y < inputGrid.getHeight(); y++) {
            std::vector<int> row;
            row.reserve(inputGrid.getWidth());
            for (int x = 0; x < inputGrid.getWidth(); x++) {
                row.push_back(0);
            }
            regionGridInput.push_back(row);
        }
        Grid<int> regionGrid(regionGridInput);

        std::vector<std::pair<int, int>> sameRegions;
        int regionID = 0;
        for (int y = 0; y < inputGrid.getHeight(); y++) {
            for (int x = 0; x < inputGrid.getWidth(); x++) {
                Position p = {x, y};
                Position left = {x - 1, y};
                Position top = {x, y - 1};
                if (y == 0 && x == 0) {
                    regionGrid.set(p, regionID);
                    regionID++;
                } else if (inputGrid.has(left) && inputGrid.has(top) && inputGrid.get(left) == inputGrid.get(p) && inputGrid.get(top) == inputGrid.get(p)) {
                    regionGrid.set(p, regionGrid.get(top));
                    if (regionGrid.get(top) != regionGrid.get(left)) {
                        sameRegions.push_back(std::make_pair(regionGrid.get(left), regionGrid.get(top)));
                    }
                } else if (inputGrid.has(left) && inputGrid.get(left) == inputGrid.get(p)) {
                    regionGrid.set(p, regionGrid.get(left));
                } else if (inputGrid.has(top) && inputGrid.get(top) == inputGrid.get(p)) {
                    regionGrid.set(p, regionGrid.get(top));
                } else {
                    regionGrid.set(p, regionID);
                    regionID++;
                }
            }
        }

        setSameRegions(regionGrid, sameRegions);

        long long sum = 0;
        for (int i = 0; i < regionID; i++) {
            const long long area = getArea(regionGrid, i);
            const long long perimeter = getPerimeter(regionGrid, i);
            const long long price = area * perimeter;
            sum += price;

            std::cout << (i + 1) << "/" << regionID << std::endl;
        }

        return std::make_pair<std::string, long long>("day 12a", std::move(sum));
    }
    std::pair<std::string, long long> Day12::solutionB() {
        return std::make_pair<std::string, long long>("day 12b", 0);
    }

} // Day12