//
// Created by Roy on 19/12/2024.
//

#include "Day19.h"

#include <algorithm>
#include <iostream>
#include <map>

namespace Day19 {

    struct PatternPart {
        bool isPattern;
        std::map<char, PatternPart> remainingParts;
    };

    using Pattern = std::map<char, PatternPart>;

    std::pair<bool, std::vector<std::string>> towelPatternMatch(const std::string &remainingTowel, const std::vector<std::string> &availablePatterns) {
        if (remainingTowel.empty()) {
            std::vector<std::string> patternMatches = {};
            return std::make_pair(true, patternMatches);
        }

        for (const auto &pattern : availablePatterns) {
            if (pattern[0] != remainingTowel[0]) continue;

            const auto match = remainingTowel.find(pattern);
            if (match != std::string::npos && match == 0) {
                const std::string newTowel = remainingTowel.substr(pattern.size(), remainingTowel.size() - pattern.size());
                const auto result = towelPatternMatch(newTowel, availablePatterns);
                if (result.first) {
                    std::vector<std::string> patternMatches = result.second;
                    patternMatches.insert(patternMatches.begin(), pattern);
                    return std::make_pair(true, patternMatches);
                }
            }
        }

        std::vector<std::string> patternMatches = {};
        return std::make_pair(false, patternMatches);
    }

    long long countTowelPatternMatches(const std::string &remainingTowel, Pattern &availablePatterns, std::map<std::string, long long> &seenSubPatterns) {
        if (remainingTowel.empty()) {
            std::vector<std::string> patternMatches = {};
            return 1;
        }

        const auto cacheMatch = seenSubPatterns.find(remainingTowel);
        if (cacheMatch != seenSubPatterns.end()) {
            return cacheMatch->second;
        }

        long long count = 0;

        Pattern* remainingPatternsP = &availablePatterns;
        for (int i = 0; i < remainingTowel.size(); i++) {
            char part = remainingTowel[i];
            const auto match = remainingPatternsP->find(part);
            if (match == remainingPatternsP->end()) break;

            if (match->second.isPattern) {
                const std::string newTowel = remainingTowel.substr(i + 1, remainingTowel.size() - i - 1);
                const auto result = countTowelPatternMatches(newTowel, availablePatterns, seenSubPatterns);
                if (result > 0) {
                    count += result;
                }
            }

            remainingPatternsP = &match->second.remainingParts;
        }

        seenSubPatterns.insert({remainingTowel, count});

        return count;
    }

    std::pair<std::string, long long> Day19::solutionA() {
        const std::vector<std::string> input = readInput(inputALocation);

        const std::vector<std::string> availablePatterns = split(input[0], ", ");
        const std::vector<std::string> towels(input.begin() + 2, input.end());

        long long count = 0;
        for (const auto &towel : towels) {
            const auto result = towelPatternMatch(towel, availablePatterns);
            if (result.first) {
                count++;
            }
        }

        return std::make_pair("day 19a", count);
    }

    std::pair<std::string, long long> Day19::solutionB() {
        const std::vector<std::string> input = readInput(inputBLocation);

        std::vector<std::string> availablePatterns = split(input[0], ", ");
        std::sort(availablePatterns.begin(), availablePatterns.end());
        Pattern patterns;
        for (const auto &rawPattern : availablePatterns) {
            Pattern* intermediatePatterns = &patterns;
            for (int i = 0; i < rawPattern.size(); i++) {
                char part = rawPattern.at(i);
                const auto match = intermediatePatterns->find(part);
                const bool isFinal = i == rawPattern.size() - 1;
                if (match != intermediatePatterns->end()) {
                    if (isFinal) match->second.isPattern = true;
                    intermediatePatterns = &match->second.remainingParts;
                } else {
                    PatternPart p{ isFinal, {} };
                    intermediatePatterns->insert({part, p});

                    const auto match2 = intermediatePatterns->find(part);
                    intermediatePatterns = &match2->second.remainingParts;
                }
            }
        }

        const std::vector<std::string> towels(input.begin() + 2, input.end());
        std::map<std::string, long long> seenSubPatterns;

        long long count = 0;
        int i = 0;
        for (const auto &towel : towels) {
            const auto result = countTowelPatternMatches(towel, patterns, seenSubPatterns);
            if (result) {
                count += result;
            }

            i++;
            std::cout << i << "/" << towels.size() << std::endl;
        }

        return std::make_pair("day 19b", count);
    }

} // Day19