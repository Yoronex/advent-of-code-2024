//
// Created by Roy on 07/12/2024.
//

#include "Day8.h"

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

namespace Day8 {

    struct Coordinate {
        int x; int y;
    };

    bool operator<(const Coordinate &lhs, const Coordinate &rhs) {
        if (lhs.x < rhs.x) return true;
        if (lhs.x > rhs.x) return false;
        if (lhs.y < rhs.y) return true;
        if (lhs.y > rhs.y) return false;

        return false;
    }

    bool nodeInGrid(const Coordinate &coord, const int gridWith, const int gridHeight) {
        return coord.x >= 0 && coord.x < gridWith && coord.y >= 0 && coord.y < gridHeight;
    }

    void printGridWithAntinodes(const std::vector<std::string> originalGrid, const std::set<Coordinate> antinodes) {
        std::vector<std::string> grid = originalGrid;
        for (const auto &node : antinodes) {
            grid[node.y][node.x] = '#';
        }

        for (const auto &line : grid) {
            std::cout << line << std::endl;
        }
        std::cout << std::endl;
    }

    std::pair<std::string, long long> Day8::solutionA() {
        const std::vector<std::string> input = readInput(inputALocation);
        const int gridWidth = input[0].size();
        const int gridHeight = input.size();

        std::map<char, std::vector<Coordinate>> antennaGroups;
        std::set<Coordinate> antinodes;

        for (int y = 0; y < input.size(); y++) {
            for (int x = 0; x < input[0].size(); x++) {
                if (input[y][x] != '.') {
                    const auto mapMatch = antennaGroups.find(input[y][x]);
                    if (mapMatch != antennaGroups.end()) {
                        mapMatch->second.push_back({ x, y });
                    } else {
                        std::vector<Coordinate> a{{ x, y }};
                        antennaGroups.insert(std::make_pair(input[y][x], a));
                    }
                }
            }
        }

        for (const auto antennas : antennaGroups) {
            for (int i = 0; i < antennas.second.size(); i++) {
                for (int j = i + 1; j < antennas.second.size(); j++) {
                    const Coordinate antennaA = antennas.second[i];
                    const Coordinate antennaB = antennas.second[j];
                    int differenceX = antennaB.x - antennaA.x;
                    int differenceY = antennaB.y - antennaA.y;

                    const Coordinate antinodeA{antennaA.x - differenceX, antennaA.y - differenceY};
                    const Coordinate antinodeB{antennaB.x + differenceX, antennaB.y + differenceY};
                    if (nodeInGrid(antinodeA, gridWidth, gridHeight)) {
                        antinodes.insert(antinodeA);
                    }
                    if (nodeInGrid(antinodeB, gridWidth, gridHeight)) {
                        antinodes.insert(antinodeB);
                    }
                }
            }
        }

        return std::make_pair("day 8a", antinodes.size());
    }

    std::pair<std::string, long long> Day8::solutionB() {
        const std::vector<std::string> input = readInput(inputBLocation);
        const int gridWidth = input[0].size();
        const int gridHeight = input.size();

        std::map<char, std::vector<Coordinate>> antennaGroups;
        std::set<Coordinate> antinodes;

        for (int y = 0; y < input.size(); y++) {
            for (int x = 0; x < input[0].size(); x++) {
                if (input[y][x] != '.') {
                    const auto mapMatch = antennaGroups.find(input[y][x]);
                    if (mapMatch != antennaGroups.end()) {
                        mapMatch->second.push_back({ x, y });
                    } else {
                        std::vector<Coordinate> a{{ x, y }};
                        antennaGroups.insert(std::make_pair(input[y][x], a));
                    }
                }
            }
        }

        for (const auto antennas : antennaGroups) {
            for (int i = 0; i < antennas.second.size(); i++) {
                for (int j = i + 1; j < antennas.second.size(); j++) {
                    const Coordinate antennaA = antennas.second[i];
                    const Coordinate antennaB = antennas.second[j];
                    antinodes.insert(antennaA);
                    antinodes.insert(antennaB);

                    int differenceX = antennaB.x - antennaA.x;
                    int differenceY = antennaB.y - antennaA.y;

                    Coordinate antinodeA{antennaA.x - differenceX, antennaA.y - differenceY};
                    Coordinate antinodeB{antennaB.x + differenceX, antennaB.y + differenceY};
                    while (nodeInGrid(antinodeA, gridWidth, gridHeight)) {
                        antinodes.insert(antinodeA);
                        antinodeA.x -= differenceX;
                        antinodeA.y -= differenceY;
                    }
                    while (nodeInGrid(antinodeB, gridWidth, gridHeight)) {
                        antinodes.insert(antinodeB);
                        antinodeB.x += differenceX;
                        antinodeB.y += differenceY;
                    }
                }
            }
        }

        printGridWithAntinodes(input, antinodes);

        return std::make_pair("day 8b", antinodes.size());
    }
} // Day8