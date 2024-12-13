//
// Created by Roy on 30/11/2024.
//

#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <string>

struct Position {
  long long x;
  long long y;

  bool operator<(const Position &rhs) const;
  bool operator>(const Position &rhs) const;
  bool operator==(const Position &rhs) const;
  bool operator!=(const Position & rhs) const;
};

template <typename T>
class Grid {

public:
  Grid(const std::vector<std::vector<T>> &grid): m_grid(grid) {}
  Grid(const std::vector<std::string> &grid);
  Grid(long long width, long long height, const T &defaultValue);

  unsigned long long getWidth() const;
  unsigned long long getHeight() const;

  void set(const Position &pos, const T &value);
  T get(const Position &pos) const;
  bool has(const Position &pos) const;

  std::vector<T> up(const Position &p) const;
  std::vector<T> down(const Position &p) const;
  std::vector<T> left(const Position &p) const;
  std::vector<T> right(const Position &p) const;

private:
  std::vector<std::vector<T>> m_grid;
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
