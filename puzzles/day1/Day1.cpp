//
// Created by Roy on 30/11/2024.
//

#include "Day1.h"

#include <algorithm>
#include <iostream>
#include <string>

std::pair<std::string, int> Day1::solutionA() {
    const auto input = readInput(inputALocation);

    std::vector<int> digits;

    for (const auto line : input) {
        std::string firstDigit;
        std::string lastDigit;
        for (const auto ch : line) {
            if (std::isdigit(ch) && firstDigit.empty()) {
                firstDigit = ch;
            }
            if (std::isdigit(ch)) {
                lastDigit = ch;
            }
        }
        digits.push_back(std::stoi(firstDigit + lastDigit));
    }

    int sum = 0;
    for (const auto digit : digits) {
        sum += digit;
    }

    return std::make_pair("Day 1a", sum);
}

std::pair<std::string, int> Day1::solutionB() {
    std::cout << "Hello world A!\n" << std::endl;
    return std::make_pair("Day 1a", 2);
}
