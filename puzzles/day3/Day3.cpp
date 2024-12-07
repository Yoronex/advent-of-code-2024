//
// Created by Roy on 03/12/2024.
//

#include "Day3.h"

#include <iostream>
#include <regex>
#include <string>
#include <vector>

std::pair<std::string, long long> Day3::solutionA() {
    auto input = readInput(inputALocation);

    int sum = 0;

    std::regex regexMul("mul\\([0-9]+,[0-9]+\\)");
    std::smatch match;
    std::cout << "regex " << match.empty() << std::endl;
    for (auto &line : input) {
        while (std::regex_search(line, match, regexMul)) {
            std::cout << line << std::endl;
            std::cout << match.size() << " matches" << std::endl;
            for (std::size_t i = 0; i < match.size(); i++) {
                const std::string mulS = match[i];
                std::cout << i << ": " << match[i] << " at " << match.position() << " of length " << match[0].length() << std::endl;
                const std::vector<std::string> numbersS = split(split(split(mulS, "(")[1], ")")[0], ",");
                int toAdd = (std::stoi(numbersS[0]) * std::stoi(numbersS[1]));
                sum += toAdd;
                std::cout << "+ " << toAdd << " = " << sum << std::endl;

                line.erase(match.position(), match[0].length());
            }
        }
    }

    return std::make_pair("Day 3a", sum);
}

std::pair<std::string, long long> Day3::solutionB() {
    auto input = readInput(inputALocation);

    int sum = 0;

    std::regex regexMul("mul\\([0-9]+,[0-9]+\\)");
    std::regex regexDo("do\\(\\)");
    std::regex regexDont("don't\\(\\)");
    std::smatch matchMul;
    std::smatch matchDo;
    std::smatch matchDont;

    bool enabled = true;

    for (auto &line : input) {
        while (std::regex_search(line, matchMul, regexMul)) {
            std::regex_search(line, matchMul, regexMul);
            std::regex_search(line, matchDo, regexDo);
            std::regex_search(line, matchDont, regexDont);

            if (!matchDo.empty() && matchDo.position(0) < matchMul.position(0) && (matchDont.empty() || matchDo.position(0) < matchDont.position(0))) {
                enabled = true;
                line.erase(matchDo.position(0), matchDo[0].length());
            } else if (!matchDont.empty() && matchDont.position() < matchMul.position()) {
                enabled = false;
                line.erase(matchDont.position(0), matchDont[0].length());
            } else {
                const std::string mulS = matchMul[0];
                if (enabled) {
                    const std::vector<std::string> numbersS = split(split(split(mulS, "(")[1], ")")[0], ",");
                    int toAdd = (std::stoi(numbersS[0]) * std::stoi(numbersS[1]));
                    sum += toAdd;
                    std::cout << "+ " << toAdd << " = " << sum << std::endl;
                } else {
                    std::cout << "Not adding " << mulS << ": not enabled" << std::endl;
                }
                line.erase(matchMul.position(0), matchMul[0].length());
            }
        }
    }

    return std::make_pair("Day 3a", sum);
}

// x&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))