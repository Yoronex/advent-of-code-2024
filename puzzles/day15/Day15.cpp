//
// Created by Roy on 14/12/2024.
//

#include "Day15.h"

#include <deque>
#include <iostream>

#include "base/Grid.h"

namespace Day15 {
    Position getCurrentPosition(const Grid<std::string> &grid) {
        for (long long x = 0; x < grid.getWidth(); x++) {
            for (long long y = 0; y < grid.getHeight(); y++) {
                if (grid.get({x, y}) == "@") {
                    return {x, y};
                }
            }
        }
        return { -1, -1 };
    }

    std::string toSingleString(const std::vector<std::string> &stringList) {
        std::string result;
        for (const auto &s : stringList) {
            result += s;
        }
        return result;
    }

    std::string getLineUntilWall(const std::string &viewLine) {
        const auto match = viewLine.find('#');
        if (match == std::string::npos) return viewLine;
        return viewLine.substr(0, match);
    }

    bool standingAgainstBox(const std::string &viewLine) {
        // standing against the wall
        if (viewLine.empty()) return false;
        return viewLine.substr(0, 1) == "O";
    }

    long long getFirstEmptySpotInLine(const std::string &viewLine) {
        const auto match = viewLine.find('.');
        if (match == std::string::npos) return -1;
        return match;
    }

    Position getNewPositionA(Grid<std::string> &grid, const char movementAction) {
        const Position currentPosition = getCurrentPosition(grid);
        Position newPosition = currentPosition;
        switch (movementAction) {
            case '^': {
                const auto viewLine = getLineUntilWall(toSingleString(grid.up(currentPosition)));
                const long long spot = getFirstEmptySpotInLine(viewLine);
                if (!viewLine.empty() && (!standingAgainstBox(viewLine) || spot >= 0)) {
                    grid.set(currentPosition, ".");
                    newPosition = {currentPosition.x, currentPosition.y - 1};
                    grid.set(newPosition, "@");
                }
                if (standingAgainstBox(viewLine) && spot >= 0) {
                    grid.set({currentPosition.x, currentPosition.y - 1 - spot}, "O");
                }
                break;
            }
            case 'v': {
                const auto viewLine = getLineUntilWall(toSingleString(grid.down(currentPosition)));
                const long long spot = getFirstEmptySpotInLine(viewLine);
                if (!viewLine.empty() && (!standingAgainstBox(viewLine) || spot >= 0)) {
                    grid.set(currentPosition, ".");
                    newPosition = {currentPosition.x, currentPosition.y + 1};
                    grid.set(newPosition, "@");
                }
                if (standingAgainstBox(viewLine) && spot >= 0) {
                    grid.set({currentPosition.x, currentPosition.y + 1+ spot}, "O");
                }
                break;
            }
            case '<': {
                const auto viewLine = getLineUntilWall(toSingleString(grid.left(currentPosition)));
                const long long spot = getFirstEmptySpotInLine(viewLine);
                if (!viewLine.empty() && (!standingAgainstBox(viewLine) || spot >= 0)) {
                    grid.set(currentPosition, ".");
                    newPosition = {currentPosition.x - 1, currentPosition.y};
                    grid.set(newPosition, "@");
                }
                if (standingAgainstBox(viewLine) && spot >= 0) {
                    grid.set({currentPosition.x - 1 - spot, currentPosition.y}, "O");
                }
                break;
            }
            case '>': {
                const auto viewLine = getLineUntilWall(toSingleString(grid.right(currentPosition)));
                const long long spot = getFirstEmptySpotInLine(viewLine);
                if (!viewLine.empty() && (!standingAgainstBox(viewLine) || spot >= 0)) {
                    grid.set(currentPosition, ".");
                    newPosition = {currentPosition.x + 1, currentPosition.y};
                    grid.set(newPosition, "@");
                }
                if (standingAgainstBox(viewLine) && spot >= 0) {
                    grid.set({currentPosition.x + 1 + spot, currentPosition.y}, "O");
                }
                break;
            }
            default: {
                // Unreachable place
                std::cout << "Unknown movement action: \"" << movementAction << "\"" << std::endl;
                throw;
            }
        }
        return newPosition;
    }

    bool canPushBox(Grid<std::string> &grid, const Position &initialBox, const char direction) {
        std::vector<Position> checkedBoxes;
        std::deque<Position> boxesToCheck{initialBox};
            switch (direction) {
                case '^': {
                    while (!boxesToCheck.empty()) {
                        const Position boxPosition = boxesToCheck[0];
                        boxesToCheck.pop_front();
                        const auto viewLineLeft = getLineUntilWall(toSingleString(grid.up(boxPosition)));
                        const auto viewLineRight = getLineUntilWall(toSingleString(grid.up({boxPosition.x + 1, boxPosition.y})));
                        // A box is standing against the wall, so it cannot be pushed
                        if (viewLineLeft.empty() || viewLineRight.empty()) return false;
                        if (viewLineLeft[0] == ']') {
                            boxesToCheck.push_back({ boxPosition.x - 1, boxPosition.y - 1});
                        }
                        if (viewLineLeft[0] == '[') {
                            boxesToCheck.push_back({boxPosition.x, boxPosition.y - 1});
                        }
                        if (viewLineRight[0] == '[') {
                            boxesToCheck.push_back({ boxPosition.x + 1, boxPosition.y - 1});
                        }
                        checkedBoxes.push_back(boxPosition);
                    }

                    // CheckedBoxes contains elements from bottom to top, but we should reverse it
                    // to not overwrite already processed boxes
                    std::reverse(checkedBoxes.begin(), checkedBoxes.end());
                    for (const auto b : checkedBoxes) {
                        grid.set({b.x, b.y - 1}, "[");
                        grid.set({b.x + 1, b.y - 1}, "]");
                        grid.set({b.x, b.y}, ".");
                        grid.set({b.x + 1, b.y}, ".");
                    }
                    return true;
                }
                case 'v': {
                    while (!boxesToCheck.empty()) {
                        const Position boxPosition = boxesToCheck[0];
                        boxesToCheck.pop_front();
                        const auto viewLineLeft = getLineUntilWall(toSingleString(grid.down(boxPosition)));
                        const auto viewLineRight = getLineUntilWall(toSingleString(grid.down({boxPosition.x + 1, boxPosition.y})));
                        // A box is standing against the wall, so it cannot be pushed
                        if (viewLineLeft.empty() || viewLineRight.empty()) return false;
                        if (viewLineLeft[0] == ']') {
                            boxesToCheck.push_back({ boxPosition.x - 1, boxPosition.y + 1});
                        }
                        if (viewLineLeft[0] == '[') {
                            boxesToCheck.push_back({boxPosition.x, boxPosition.y + 1});
                        }
                        if (viewLineRight[0] == '[') {
                            boxesToCheck.push_back({ boxPosition.x + 1, boxPosition.y + 1});
                        }
                        checkedBoxes.push_back(boxPosition);
                    }

                    // CheckedBoxes contains elements from top to bottom, but we should reverse it
                    // to not overwrite already processed boxes
                    std::reverse(checkedBoxes.begin(), checkedBoxes.end());
                    for (const auto b : checkedBoxes) {
                        grid.set({b.x, b.y + 1}, "[");
                        grid.set({b.x + 1, b.y + 1}, "]");
                        grid.set({b.x, b.y}, ".");
                        grid.set({b.x + 1, b.y}, ".");
                    }
                    return true;
                }
                case '<': {
                    const auto viewLine = getLineUntilWall(toSingleString(grid.left(initialBox)));
                    const long long spot = getFirstEmptySpotInLine(viewLine);
                    if (viewLine.empty()) return false;
                    if (spot < 0) return false;
                    for (long long i = 0; i < spot + 1; i++) {
                        long long x = initialBox.x - 1 - spot + i;
                        if (i % 2 == 0) {
                            grid.set({ x, initialBox.y }, "[");
                        } else {
                            grid.set({ x, initialBox.y }, "]");
                        }
                    }
                    grid.set({ initialBox.x, initialBox. y}, ".");
                    return true;
                }
                case '>': {
                    const auto viewLine = getLineUntilWall(toSingleString(grid.right(initialBox)));
                    const long long spot = getFirstEmptySpotInLine(viewLine);
                    if (viewLine.empty()) return false;
                    if (spot < 0) return false;
                    for (long long i = 0; i < spot + 1; i++) {
                        long long x = initialBox.x + 1 + i;
                        if (i % 2 == 0) {
                            grid.set({ x, initialBox.y }, "[");
                        } else {
                            grid.set({ x, initialBox.y }, "]");
                        }
                    }
                    grid.set({ initialBox.x, initialBox. y}, ".");
                    return true;
                }
            default: {
                // Unreachable place
                std::cout << "Unknown movement action: \"" << direction << "\"" << std::endl;
                throw;
            }
        }
    }

    Position getNewPositionB(Grid<std::string> &grid, const char movementAction) {
        const Position p = getCurrentPosition(grid);
        Position newPosition = p;
        switch (movementAction) {
            case '^': {
                const auto viewLine = getLineUntilWall(toSingleString(grid.up(p)));
                if (viewLine.empty()) break;
                if (viewLine.at(0) == '.'
                    || (viewLine.at(0) == '[' && canPushBox(grid, {  p.x , p.y - 1 }, movementAction))
                    || (viewLine.at(0) == ']' && canPushBox(grid, {  p.x - 1 , p.y - 1 }, movementAction))
                ) {
                    grid.set(p, ".");
                    newPosition = {p.x, p.y - 1};
                    grid.set(newPosition, "@");
                }
                break;
            }
            case 'v': {
                const auto viewLine = getLineUntilWall(toSingleString(grid.down(p)));
                if (viewLine.empty()) break;
                if (viewLine.at(0) == '.'
                    || (viewLine.at(0) == '[' && canPushBox(grid, {  p.x , p.y + 1 }, movementAction))
                    || (viewLine.at(0) == ']' && canPushBox(grid, {  p.x - 1 , p.y + 1 }, movementAction))
                ) {
                    grid.set(p, ".");
                    newPosition = {p.x, p.y + 1};
                    grid.set(newPosition, "@");
                }
                break;
            }
            case '<': {
                const auto viewLine = getLineUntilWall(toSingleString(grid.left(p)));
                if (viewLine.empty()) break;
                if (viewLine.at(0) == '.' || (viewLine.at(0) == ']' && canPushBox(grid, {  p.x - 1 , p.y }, movementAction))) {
                    grid.set(p, ".");
                    newPosition = {p.x - 1, p.y};
                    grid.set(newPosition, "@");
                }
                break;
            }
            case '>': {
                const auto viewLine = getLineUntilWall(toSingleString(grid.right(p)));
                if (viewLine.empty()) break;
                if (viewLine.at(0) == '.' || (viewLine.at(0) == '[' && canPushBox(grid, {  p.x + 1 , p.y }, movementAction))) {
                    grid.set(p, ".");
                    newPosition = {p.x + 1, p.y};
                    grid.set(newPosition, "@");
                }
                break;
            }
            default: {
                // Unreachable place
                std::cout << "Unknown movement action: \"" << movementAction << "\"" << std::endl;
                throw;
            }
        }
        return newPosition;
    }

    void printGrid(const Grid<std::string> &grid) {
        for (long long y = 0; y < grid.getHeight(); y++) {
            std::string row;
            for (long long x = 0; x < grid.getWidth(); x++) {
                row += grid.get({ x, y });
            }
            std::cout << row << std::endl;
        }
    }

    std::pair<std::string, long long> Day15::solutionA() {
        const std::vector<std::string> input = readInput(inputALocation);
        std::vector<std::vector<std::string>> separatedInput;
        std::vector<std::string> inputPart;
        for (const auto &row : input) {
            if (row.empty()) {
                separatedInput.push_back(inputPart);
                inputPart = {};
            } else {
                inputPart.push_back(row);
            }
        }
        separatedInput.push_back(inputPart);

        Grid<std::string> grid(separatedInput[0]);
        std::string movements;
        for (const auto &row : separatedInput[1]) {
            movements += row;
        }

        Position currentPosition = getCurrentPosition(grid);
        for (const auto action : movements) {
            currentPosition = getNewPositionA(grid, action);
            // std::cout << "Move " << action << std::endl;
            // printGrid(grid);
            // std::cout << std::endl;
        }

        long long sum = 0;
        for (long long y = 0; y < grid.getHeight(); y++) {
            for (long long x = 0; x < grid.getWidth(); x++) {
                if (grid.get({x, y}) == "O") {
                    sum += (y * 100) + x;
                }
            }
        }

        return std::make_pair("day 15a", sum);
    }

    std::pair<std::string, long long> Day15::solutionB() {
        const std::vector<std::string> input = readInput(inputALocation);
        std::vector<std::vector<std::string>> separatedInput;
        std::vector<std::string> inputPart;
        for (const auto &row : input) {
            if (row.empty()) {
                separatedInput.push_back(inputPart);
                inputPart = {};
            } else {
                inputPart.push_back(row);
            }
        }
        separatedInput.push_back(inputPart);

        std::vector<std::string> scaledGrid;
        scaledGrid.reserve(separatedInput[0].size());
        for (const auto &row : separatedInput[0]) {
            std::string newRow;
            for (const auto c : row) {
                if (c == 'O') {
                    newRow += "[]";
                } else if (c == '@') {
                    newRow += "@.";
                } else {
                    newRow += c;
                    newRow += c;
                }
            }
            scaledGrid.push_back(newRow);
        }
        Grid<std::string> grid(scaledGrid);

        std::string movements;
        for (const auto &row : separatedInput[1]) {
            movements += row;
        }

        std::cout << "Initial state:" << std::endl;
        printGrid(grid);
        std::cout << std::endl;

        Position currentPosition = getCurrentPosition(grid);
        for (const auto action : movements) {
            currentPosition = getNewPositionB(grid, action);
            // std::cout << "Move " << action << std::endl;
            // printGrid(grid);
            // std::cout << std::endl;
        }

        long long sum = 0;
        for (long long y = 0; y < grid.getHeight(); y++) {
            for (long long x = 0; x < grid.getWidth(); x++) {
                if (grid.get({x, y}) == "[") {
                    sum += (y * 100) + x;
                }
            }
        }

        return std::make_pair("day 15a", sum);
    }

} // Day15