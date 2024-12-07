//
// Created by Roy on 06/12/2024.
//

#include "Day7.h"

#include <iostream>

namespace Day7 {
    typedef std::pair<long long, std::vector<long long>> Equation;

    bool canBeTrue(const Equation &eq, const long long index, const long long intResult, const bool useConcatenation) {
        if (eq.second.size() == index && intResult == eq.first) return true;
        if (eq.second.size() == index && intResult != eq.first) return false;
        if (intResult > eq.first) return false;

        long long nextValue = eq.second[index];
        bool canPlus = canBeTrue(eq, index + 1, intResult + nextValue, useConcatenation);
        bool canMultiply = canBeTrue(eq, index + 1, intResult * nextValue, useConcatenation);
        bool canConcatenate = false;
        if (useConcatenation) {
            long long newIntermediate = std::stoll(std::to_string(intResult) + std::to_string(nextValue));
            canConcatenate = canBeTrue(eq, index + 1, newIntermediate, useConcatenation);
        }
        return canPlus || canMultiply || canConcatenate;
    }

    std::pair<std::string, long long> Day7::solutionA() {
        const std::vector<std::string> input = readInput(inputALocation);
        std::vector<Equation> equations;
        for (const auto &row : input) {
            auto eqResult = split(row, ": ");
            auto values = split(eqResult[1], " ");
            std::vector<long long> valuesVector;
            valuesVector.reserve(values.size());
            for (const auto &v : values) {
                valuesVector.push_back(std::stoll(v));
            }
            equations.emplace_back(std::stoll(eqResult[0]), valuesVector);
        }

        long long validEquations = 0;
        std::vector<long long> validResults;

        for (auto &eq : equations) {
            long long firstValue = eq.second[0];
            if (canBeTrue(eq, 1, firstValue, false)) {
                validEquations++;
                validResults.push_back(eq.first);
            }
        }

        long long result = 0;
        for (auto v : validResults) {
            result += v;
        }

        return std::make_pair("day 7a", result);
    }

    std::pair<std::string, long long> Day7::solutionB() {
        const std::vector<std::string> input = readInput(inputALocation);
        std::vector<Equation> equations;
        for (const auto &row : input) {
            auto eqResult = split(row, ": ");
            auto values = split(eqResult[1], " ");
            std::vector<long long> valuesVector;
            valuesVector.reserve(values.size());
            for (const auto &v : values) {
                valuesVector.push_back(std::stoll(v));
            }
            equations.emplace_back(std::stoll(eqResult[0]), valuesVector);
        }

        long long validEquations = 0;
        std::vector<long long> validResults;

        for (auto &eq : equations) {
            long long firstValue = eq.second[0];
            if (canBeTrue(eq, 1, firstValue, true)) {
                validEquations++;
                validResults.push_back(eq.first);
            }
        }

        long long result = 0;
        for (auto v : validResults) {
            result += v;
        }

        return std::make_pair("day 7b", result);
    }
} // Day7