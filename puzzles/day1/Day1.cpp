//
// Created by Roy on 30/11/2024.
//

#include "Day1.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <map>

bool comp(const int a, const int b) {
    return a < b;
}

std::pair<std::string, int> Day1::solutionA() {
    const auto input = readInput(inputALocation);
    std::vector<std::pair<int, int>> matrix;
    std::vector<int> leftCol;
    std::vector<int> rightCol;

    for (const auto &row : input) {
        auto cols = split(row, "  ");
        int left = std::stoi(cols[0]);
        int right = std::stoi(cols[1]);
        std::pair<int, int> newRow = std::make_pair(left, right);
        matrix.push_back(newRow);
        leftCol.push_back(left);
        rightCol.push_back(right);
    }

    std::sort(leftCol.begin(), leftCol.end(), comp);
    std::sort(rightCol.begin(), rightCol.end(), comp);

    std::vector<int> distances;
    for (int i = 0; i < leftCol.size(); i++) {
        const int leftValue = leftCol[i];
        const int rightValue = rightCol[i];

        if (leftValue > rightValue) {
            distances.push_back(leftValue - rightValue);
        } else {
            distances.push_back(rightValue - leftValue);
        }
    }

    int sum = 0;
    for (const auto digit : distances) {
        sum += digit;
    }

    return std::make_pair("Day 1a", sum);
}

std::pair<std::string, int> Day1::solutionB() {
    const auto input = readInput(inputALocation);
    std::vector<std::pair<int, int>> matrix;
    std::vector<int> leftCol;
    std::vector<int> rightCol;

    for (const auto &row : input) {
        auto cols = split(row, "  ");
        int left = std::stoi(cols[0]);
        int right = std::stoi(cols[1]);
        std::pair<int, int> newRow = std::make_pair(left, right);
        matrix.push_back(newRow);
        leftCol.push_back(left);
        rightCol.push_back(right);
    }

    std::sort(leftCol.begin(), leftCol.end(), comp);
    std::sort(rightCol.begin(), rightCol.end(), comp);

    // Map from right digit to count
    std::map<int, int> occurences;
    for (const auto val : rightCol) {
        auto match = occurences.find(val);
        if (match == occurences.end()) {
            occurences.insert(std::make_pair(val, 1));
        } else {
            match->second++;
        }
    }

    int score = 0;
    for (const auto &row : matrix) {
        auto match = occurences.find(row.first);
        if (match != occurences.end()) {
            score += (row.first * match->second);
        }
    }

    return std::make_pair("Day 1b", score);
}
