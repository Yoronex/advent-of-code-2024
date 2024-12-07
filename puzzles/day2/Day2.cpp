//
// Created by Roy on 30/11/2024.
//

#include "Day2.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <map>


std::pair<std::string, long long> Day2::solutionA() {
    const auto input = readInput(inputALocation);
    std::vector<std::vector<int>> matrix;
    std::vector<int> safeInputs;

    for (const auto &row : input) {
        auto cols = split(row, " ");
        std::vector<int> newRow;
        for (const auto &col : cols) {
          newRow.push_back(std::stoi(col));
        }
        matrix.push_back(newRow);
    }

    bool decreasing = false;
    for (const auto &row : matrix) {
        bool result = true;
        for (int i = 0; i < row.size() - 1; i++) {
            // Row should be decreasing
            if (i == 0 && row[i] > row[i + 1]) {
                decreasing = true;
            // Row should be increasing
            } else if (i == 0 && row[i] < row[i + 1]) {
                decreasing = false;
            } else if (i == 0) {
                result = false;
                break;
            }

            if (decreasing) {
                if (row[i] <= row[i + 1] || row[i] > row[i + 1] + 3) {
                    result = false;
                    break;
                }
            } else {
                if (row[i] >= row[i + 1] || row[i] + 3 < row[i + 1]) {
                    result = false;
                    break;
                }
            }
        }
        safeInputs.push_back(result);
    }

    int sum = 0;
    for (const auto digit : safeInputs) {
        sum += digit;
    }

    return std::make_pair("Day 2a", sum);
}

bool Day2::solution_isSafe(const std::vector<int> &row) {
    bool decreasing = false;
    for (int i = 0; i < row.size() - 1; i++) {
        // Row should be decreasing
        if (i == 0 && row[i] > row[i + 1]) {
            decreasing = true;
            // Row should be increasing
        } else if (i == 0 && row[i] < row[i + 1]) {
            decreasing = false;
        } else if (i == 0) {
            return false;
        }

        if (decreasing) {
            if (row[i] <= row[i + 1] || row[i] > row[i + 1] + 3) {
                return false;
            }
        } else {
            if (row[i] >= row[i + 1] || row[i] + 3 < row[i + 1]) {
                return false;
            }
        }
    }
    return true;
}

std::pair<std::string, long long> Day2::solutionB() {
    const auto input = readInput(inputALocation);
    std::vector<std::vector<int>> matrix;
    std::vector<int> safeInputs;

    for (const auto &row : input) {
        auto cols = split(row, " ");
        std::vector<int> newRow;
        for (const auto &col : cols) {
            newRow.push_back(std::stoi(col));
        }
        matrix.push_back(newRow);
    }

    for (const auto &row : matrix) {
        if (Day2::solution_isSafe(row)) {
          safeInputs.push_back(true);
          continue;
        }

        bool result = false;
        for (int i = 0; i < row.size(); i++) {
            std::vector<int> newRow = row;
            newRow.erase(newRow.begin() + i);

            if (Day2::solution_isSafe(newRow)) {
                result = true;
                break;
            }
        }
        safeInputs.push_back(result);
    }

    int sum = 0;
    for (const auto digit : safeInputs) {
        sum += digit;
    }

    return std::make_pair("Day 2b", sum);
}
