//
// Created by Roy on 30/11/2024.
//

#include "Solution.h"

#include <iostream>
#include <fstream>

std::vector<std::string> Solution::readInput(const std::string &fileLocation) {
    std::ifstream file(fileLocation);

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
      lines.push_back(line);
    }

    return lines;
};

std::vector<std::string> Solution::split(const std::string &toSplit, const std::string &delimiter) {
    std::string s = toSplit;

    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
};

//Solution::~Solution() = default;

std::pair<std::string, long long> Solution::solutionA() {
    return {"defaultA", 0};
}

std::pair<std::string, long long> Solution::solutionB() {
    return {"defaultB", 0};
}