//
// Created by Roy on 15/12/2024.
//

#ifndef GRID_H
#define GRID_H
#include <string>
#include <vector>


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

#define GRID_FUNCTIONS
#include "Grid.cpp"

#endif //GRID_H
