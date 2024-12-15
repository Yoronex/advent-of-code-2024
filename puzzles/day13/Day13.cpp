//
// Created by Roy on 13/12/2024.
//

#include "Day13.h"
#include <cmath>

#include "base/Grid.h"

namespace Day13 {

    struct Game {
        Position buttonAMovement;
        Position buttonBMovement;
        Position goal;
    };

    Position parseGameInput(const std::string &row) {
        int offset;
        if (row.substr(10, 2) == "X+") {
            offset = 10;
        } else {
            offset = 7;
        }

        const int commaPosition = row.find(',');
        const std::string xInput = row.substr(offset + 2, commaPosition - offset - 2);
        const std::string yInput = row.substr(commaPosition + 4, row.size() - commaPosition - 4);
        const int x = std::stoi(xInput);
        const int y = std::stoi(yInput);

        return {x, y};
    }

    std::pair<long long, long long> findButtonPresses(const Game &game) {
        std::vector<std::vector<Position>> grid;
        std::vector<std::pair<int, int>> validSolutions;
        const long long maxAPresses = std::min((game.goal.x / game.buttonAMovement.x + 1), (game.goal.y / game.buttonAMovement.y + 1)) + 1;
        const long long maxBPresses = std::min((game.goal.x / game.buttonBMovement.x + 1), (game.goal.y / game.buttonBMovement.y + 1)) + 1;

        for (int bPresses = 0; bPresses < maxBPresses + 1; bPresses++) {
            std::vector<Position> row;
            for (int aPresses = 0; aPresses < maxAPresses + 1; aPresses++) {
                if (aPresses == 0 && bPresses == 0) {
                    row.push_back({ 0, 0 });
                } else if (aPresses == 0) {
                    // Button b press
                    const Position prev = grid[bPresses - 1][aPresses];
                    row.push_back({ prev.x + game.buttonBMovement.x, prev.y + game.buttonBMovement.y });
                } else {
                    // button a press
                    const Position prev = row[aPresses - 1];
                    const Position score = { prev.x + game.buttonAMovement.x, prev.y + game.buttonAMovement.y };
                    row.push_back(score);
                    // We have met the goal!
                    if (score.x == game.goal.x && score.y == game.goal.y) {
                        validSolutions.emplace_back(aPresses, bPresses);
                        break;
                    }
                    // We have overshot our goal
                    if (score.x > game.goal.x || score.y > game.goal.y) break;
                }
            }
            grid.push_back(row);
        }

        if (validSolutions.empty()) return std::make_pair(-1, -1);
        if (validSolutions.size() == 1) return validSolutions[0];
        std::vector<int> tokenCosts;
        int minCosts = INT_MAX;
        int minPosition = 0;
        for (const auto &solution : validSolutions) {
            tokenCosts.push_back(solution.first * 3 + solution.second);
        }
        for (int i = 0; i < tokenCosts.size(); i++) {
            const int costs = tokenCosts[i];
            if (costs < minCosts) {
                minCosts = costs;
                minPosition = i;
            }
        }
        return validSolutions[minPosition];
    }

    std::pair<long long, long long> findButtonPressesFast(const Game &game) {
        long double divisionFactor = (game.buttonAMovement.x * game.buttonBMovement.y) - (game.buttonBMovement.x * game.buttonAMovement.y);
        if (divisionFactor == 0) return std::make_pair(-1, -1);
        long double a = ((game.goal.x * game.buttonBMovement.y) - (game.buttonBMovement.x * game.goal.y)) / divisionFactor;
        long double b = ((game.buttonAMovement.x * game.goal.y) - (game.goal.x * game.buttonAMovement.y)) / divisionFactor;

        if (a == std::floor(a) && b == std::floor(b) && a >= 0 && b >= 0) {
            return std::make_pair(a, b);
        }

        return std::make_pair(-1, -1);
    }

    std::pair<std::string, long long> Day13::solutionA() {
        const std::vector<std::string> input = readInput(inputALocation);
        std::vector<std::vector<std::string>> gameInput;
        std::vector<std::string> currentGame;
        for (const auto &row : input) {
            if (row.empty()) {
                gameInput.push_back(currentGame);
                currentGame = {};
            } else {
                currentGame.push_back(row);
            }
        }
        gameInput.push_back(currentGame);

        std::vector<Game> games;
        games.reserve(gameInput.size());
        for (const auto &game : gameInput) {
            const std::string buttonAInput = game[0];
            const std::string buttonBInput = game[1];
            const std::string prize = game[2];

            games.push_back({
                parseGameInput(buttonAInput),
                parseGameInput(buttonBInput),
                parseGameInput(prize),
            });
        }

        long long totalCosts = 0;
        for (const auto game : games) {
            std::pair<long long, long long> buttonPresses = findButtonPresses(game);
            if (buttonPresses.first < 0 || buttonPresses.second < 0) continue;

            const long long costs = buttonPresses.first * 3 + buttonPresses.second;
            totalCosts += costs;
        }

        return std::make_pair("day 13a", totalCosts);
    }

    std::pair<std::string, long long> Day13::solutionB() {
        const std::vector<std::string> input = readInput(inputALocation);
        std::vector<std::vector<std::string>> gameInput;
        std::vector<std::string> currentGame;
        for (const auto &row : input) {
            if (row.empty()) {
                gameInput.push_back(currentGame);
                currentGame = {};
            } else {
                currentGame.push_back(row);
            }
        }
        gameInput.push_back(currentGame);

        std::vector<Game> games;
        games.reserve(gameInput.size());
        for (const auto &game : gameInput) {
            const std::string buttonAInput = game[0];
            const std::string buttonBInput = game[1];
            const std::string prizeInput = game[2];

            const Position prize = parseGameInput(prizeInput);

            games.push_back({
                parseGameInput(buttonAInput),
                parseGameInput(buttonBInput),
                { prize.x + 10000000000000, prize.y + 10000000000000 },
                // prize,
            });
        }

        long long totalCosts = 0;
        for (const auto game : games) {
            std::pair<long long, long long> buttonPresses = findButtonPressesFast(game);
            if (buttonPresses.first < 0 || buttonPresses.second < 0) continue;

            const long long costs = buttonPresses.first * 3 + buttonPresses.second;
            totalCosts += costs;
        }

        return std::make_pair("day 13b", totalCosts);
    }

} // Day13