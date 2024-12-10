//
// Created by Roy on 30/11/2024.
//

#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <string>

struct Position {
  int x;
  int y;
};

class Solution {
public:
  virtual ~Solution() = default;

  virtual std::pair<std::string, long long> solutionA();
  virtual std::pair<std::string, long long> solutionB();
protected:
  std::string inputALocation;
  std::string inputBLocation;

  std::vector<std::string> readInput(const std::string &fileLocation);
  std::vector<std::string> split(const std::string &s, const std::string &delim);
};

inline bool comp(const int a, const int b) {
  return a < b;
}

#endif //SOLUTION_H
