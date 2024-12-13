//
// Created by Roy on 30/11/2024.
//

#include "Solution.h"

#include <algorithm>
#include <iostream>
#include <fstream>

bool Position::operator<(const Position &rhs) const {
    if (this->x < rhs.x) return true;
    if (this->x > rhs.x) return false;
    if (this->y < rhs.y) return true;
    if (this->y > rhs.y) return false;
    return false;
}

bool Position::operator>(const Position &rhs) const {
    return rhs < *this;
}

bool Position::operator==(const Position &rhs) const {
    return !(rhs < *this) && !(rhs > *this);
}

bool Position::operator!=(const Position &rhs) const {
    return !(*this == rhs);
}

template<>
Grid<std::string>::Grid(const std::vector<std::string> &grid) {
    for (const auto &row : grid) {
        std::vector<std::string> newRow;
        newRow.reserve(row.size());
        for (int i = 0; i < row.size(); i++) {
            newRow.push_back(row.substr(i, 1));
        }
        m_grid.emplace_back(newRow);
    }
}
template<>
Grid<int>::Grid(const std::vector<std::string> &grid) {
    for (const auto &row : grid) {
        std::vector<std::string> newRow;
        newRow.reserve(row.size());
        for (int i = 0; i < row.size(); i++) {
            newRow.push_back(row.substr(i, 1));
        }
        std::vector<int> newRowInt;
        std::transform(newRow.begin(), newRow.end(), std::back_inserter(newRowInt), [](const std::string &s) -> int {
            return std::stoi(s);
        });
        m_grid.emplace_back(newRowInt);
    }
}
template<>
Grid<long long>::Grid(const std::vector<std::string> &grid) {
    for (const auto &row : grid) {
        std::vector<std::string> newRow;
        newRow.reserve(row.size());
        for (int i = 0; i < row.size(); i++) {
            newRow.push_back(row.substr(i, 1));
        }
        std::vector<long long> newRowLongLong;
        std::transform(newRow.begin(), newRow.end(), std::back_inserter(newRowLongLong), [](const std::string &s) -> long long {
            return std::stoll(s);
        });
        m_grid.emplace_back(newRowLongLong);
    }
}
template<>
Grid<int>::Grid(long long width, long long height, const int &defaultValue) {
    m_grid.reserve(height);
    for (long long y = 0; y < height; y++) {
        std::vector<int> row;
        row.reserve(width);
        for (long long x = 0; x < width; x++) {
            row.push_back(defaultValue);
        }
        m_grid.push_back(row);
    }
}


template<>
unsigned long long Grid<std::string>::getHeight() const { return m_grid.size(); }
template<>
unsigned long long Grid<long long>::getHeight() const { return m_grid.size(); }
template<>
unsigned long long Grid<int>::getHeight() const { return m_grid.size(); }

template<>
unsigned long long Grid<std::string>::getWidth() const { return m_grid[0].size(); }
template<>
unsigned long long Grid<long long>::getWidth() const { return m_grid[0].size(); }
template<>
unsigned long long Grid<int>::getWidth() const { return m_grid[0].size(); }

template<>
void Grid<std::string>::set(const Position &pos, const std::string &value) { m_grid[pos.y][pos.x] = value; }
template<>
void Grid<long long>::set(const Position &pos, const long long &value) { m_grid[pos.y][pos.x] = value; }
template<>
void Grid<int>::set(const Position &pos, const int &value) { m_grid[pos.y][pos.x] = value; }

template<>
std::string Grid<std::string>::get(const Position &pos) const { return m_grid[pos.y][pos.x]; }
template<>
long long Grid<long long>::get(const Position &pos) const { return m_grid[pos.y][pos.x]; }
template<>
int Grid<int>::get(const Position &pos) const { return m_grid[pos.y][pos.x]; }

template<>
bool Grid<std::string>::has(const Position &pos) const {
    return pos.x >= 0 && pos.x < getWidth()
        && pos.y >= 0 && pos.y < getHeight();
}
template<>
bool Grid<long long>::has(const Position &pos) const {
    return pos.x >= 0 && pos.x < getWidth()
        && pos.y >= 0 && pos.y < getHeight();
}
template<>
bool Grid<int>::has(const Position &pos) const {
    return pos.x >= 0 && pos.x < getWidth()
        && pos.y >= 0 && pos.y < getHeight();
}

template<>
std::vector<int> Grid<int>::up(const Position &p) const {
    std::vector<int> result;
    for (int y = 0; y < p.y; y++) {
        result.push_back(get({p.x, y}));
    }
    return result;
}
template<>
std::vector<int> Grid<int>::down(const Position &p) const {
    std::vector<int> result;
    for (int y = p.y + 1; y < getHeight(); y++) {
        result.push_back(get({p.x, y}));
    }
    return result;
}
template<>
std::vector<int> Grid<int>::left(const Position &p) const {
    std::vector<int> result;
    for (int x = 0; x < p.y; x++) {
        result.push_back(get({x, p.y}));
    }
    return result;
}
template<>
std::vector<int> Grid<int>::right(const Position &p) const {
    std::vector<int> result;
    for (int x = p.x + 1; x < getWidth(); x++) {
        result.push_back(get({x, p.y}));
    }
    return result;
}


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