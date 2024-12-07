//
// Created by Roy on 03/12/2024.
//

#include "Day4.h"

#include <iostream>

bool day4IsXmasA(const std::string &input) {
    return input == "XMAS" || input == "SAMX";
}

bool day4IsXmasB(const std::string &input) {
    return input == "MAS" || input == "SAM";
}

std::pair<std::string, long long> Day4::solutionA() {
    const auto input = readInput(inputALocation);
    const int rows = input.size();
    const int cols = input[0].size();

    int occurences = 0;

    // Count horizontal
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols - 3; x++) {
            if (day4IsXmasA(input[y].substr(x, 4))) {
                occurences += 1;
            }
        }
    }

    // Count vertical
    for (int x = 0; x < cols; x++) {
        for (int y = 0; y < rows - 3; y++) {
            std::string sample = input[y].substr(x, 1) + input[y + 1].substr(x, 1) + input[y + 2].substr(x, 1) + input[y + 3].substr(x, 1);\
            if (day4IsXmasA(sample)) {
                occurences += 1;
            }
        }
    }

    // Diagonals
    for (int x = 0; x < cols - 3; x++) {
        for (int y = 0; y < rows - 3; y++) {
            // From top left to bottom right
            std::string sample1 = input[y].substr(x, 1) + input[y + 1].substr(x + 1, 1) + input[y + 2].substr(x + 2, 1) + input[y + 3].substr(x + 3, 1);
            if (day4IsXmasA(sample1)) {
                occurences += 1;
            }

            // From bottom left to top right
            std::string sample2 = input[y + 3].substr(x, 1) + input[y + 2].substr(x + 1, 1) + input[y + 1].substr(x + 2, 1) + input[y].substr(x + 3, 1);
            if (day4IsXmasA(sample2)) {
                occurences += 1;
            }
        }
    }

    return std::make_pair("day 4a", occurences);
}
std::pair<std::string, long long> Day4::solutionB() {
    const auto input = readInput(inputALocation);
    const int rows = input.size();
    const int cols = input[0].size();

    int occurences = 0;

    // Diagonals
    for (int x = 0; x < cols - 2; x++) {
        for (int y = 0; y < rows - 2; y++) {
            std::string sample1 = input[y].substr(x, 1) + input[y + 1].substr(x + 1, 1) + input[y + 2].substr(x + 2, 1);
            std::string sample2 = input[y + 2].substr(x, 1) + input[y + 1].substr(x + 1, 1) + input[y].substr(x + 2, 1);
            if (day4IsXmasB(sample1) && day4IsXmasB(sample2)) {
                occurences += 1;
            }
        }
    }

    return std::make_pair("day 4b", occurences);
}