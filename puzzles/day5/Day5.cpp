//
// Created by Roy on 04/12/2024.
//

#include "Day5.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <set>

std::pair<std::string, int> Day5::solutionA() {
    const auto input = readInput(inputALocation);

    std::map<int, std::set<int>> rulesXBeforeY;
    std::vector<std::vector<int>> updates;

    bool parseUpdates = false;
    int countRules = 0;
    for (const auto &row : input) {
        if (row.empty()) {
            parseUpdates = true;
            continue;
        }
        if (!parseUpdates) {
            auto ruleString = split(row, "|");
            int pageBefore = std::stoi(ruleString[0]);
            int pageAfter = std::stoi(ruleString[1]);
            countRules++;

            const auto match = rulesXBeforeY.find(pageBefore);
            if (match == rulesXBeforeY.end()) {
                std::set<int> afterPages{pageAfter};
                rulesXBeforeY.insert(std::make_pair(pageBefore, afterPages));
            } else {
                match->second.insert(pageAfter);
            }
        } else {
            auto pageNumbersStrings = split(row, ",");
            std::vector<int> pageUpdate;
            for (const auto &str : pageNumbersStrings) {
                pageUpdate.push_back(std::stoi(str));
            }
            updates.push_back(pageUpdate);
        }
    }

    int createdUpdates = 0;
    for (const auto &pageRule : rulesXBeforeY) {
        createdUpdates += pageRule.second.size();
    }

    std::cout << "Correctly created rules? " << (createdUpdates == countRules) << std::endl;

    std::vector<bool> updateIsCorrect;
    for (const auto &update : updates) {
        bool result = true;
        for (int i = 0; i < update.size(); i++) {
            if (!result) break;
            int page = update[i];

            const auto applicableRules = rulesXBeforeY.find(page);

            if (i < update.size() - 1 && applicableRules != rulesXBeforeY.end()) {
                for (int j = i + 1; j < update.size(); j++) {
                    int nextPage = update[j];
                    const auto match = applicableRules->second.find(nextPage);
                    if (match == applicableRules->second.end()) {
                        // Rule not found
                        result = false;
                        break;
                    }
                }
            } else if (i < update.size() - 1) {
                result = false;
            }
        }
        updateIsCorrect.push_back(result);
    }

    int sum = 0;
    for (int i = 0; i < updates.size(); i++) {
        if (updateIsCorrect[i]) {
            const auto row = updates[i];
            sum += row[row.size() / 2];
        }
    }

    return std::make_pair("day 5a", sum);
}
std::pair<std::string, int> Day5::solutionB() {
    const auto input = readInput(inputALocation);

    std::map<int, std::set<int>> rulesXBeforeY;
    std::vector<std::vector<int>> updates;

    bool parseUpdates = false;
    int countRules = 0;
    for (const auto &row : input) {
        if (row.empty()) {
            parseUpdates = true;
            continue;
        }
        if (!parseUpdates) {
            auto ruleString = split(row, "|");
            int pageBefore = std::stoi(ruleString[0]);
            int pageAfter = std::stoi(ruleString[1]);
            countRules++;

            const auto match = rulesXBeforeY.find(pageBefore);
            if (match == rulesXBeforeY.end()) {
                std::set<int> afterPages{pageAfter};
                rulesXBeforeY.insert(std::make_pair(pageBefore, afterPages));
            } else {
                match->second.insert(pageAfter);
            }
        } else {
            auto pageNumbersStrings = split(row, ",");
            std::vector<int> pageUpdate;
            for (const auto &str : pageNumbersStrings) {
                pageUpdate.push_back(std::stoi(str));
            }
            updates.push_back(pageUpdate);
        }
    }

    int createdUpdates = 0;
    for (const auto &pageRule : rulesXBeforeY) {
        createdUpdates += pageRule.second.size();
    }

    std::cout << "Correctly created rules? " << (createdUpdates == countRules) << std::endl;

    std::vector<bool> updateIsCorrect;
    for (const auto &update : updates) {
        bool result = true;
        for (int i = 0; i < update.size(); i++) {
            if (!result) break;
            int page = update[i];

            const auto applicableRules = rulesXBeforeY.find(page);

            if (i < update.size() - 1 && applicableRules != rulesXBeforeY.end()) {
                for (int j = i + 1; j < update.size(); j++) {
                    int nextPage = update[j];
                    const auto match = applicableRules->second.find(nextPage);
                    if (match == applicableRules->second.end()) {
                        // Rule not found
                        result = false;
                        break;
                    }
                }
            } else if (i < update.size() - 1) {
                result = false;
            }
        }
        updateIsCorrect.push_back(result);
    }

    int sum = 0;
    for (int i = 0; i < updates.size(); i++) {
        if (!updateIsCorrect[i]) {
            auto row = updates[i];
            std::sort(row.begin(), row.end(), [rulesXBeforeY](const int a, const int b) {
                const auto ruleAboutA = rulesXBeforeY.find(a);
                return ruleAboutA != rulesXBeforeY.end() && ruleAboutA->second.find(b) != ruleAboutA->second.end();
            });
            sum += row[row.size() / 2];
        }
    }

    return std::make_pair("day 5b", sum);
}
