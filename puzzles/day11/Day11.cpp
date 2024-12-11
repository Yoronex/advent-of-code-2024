//
// Created by Roy on 11/12/2024.
//

#include "Day11.h"

#include <algorithm>
#include <iostream>
#include <map>

namespace Day11 {
    std::vector<std::string> applyRule(const std::string &stone) {
        std::vector<std::string> result;
        if (stone == "0") {
            result.emplace_back("1");
            return result;
        }
        if (stone.size() % 2 == 0) {
            std::string firstNewStone = stone.substr(0, stone.size() / 2);
            std::string secondNewStone = stone.substr(stone.size() / 2, stone.size() / 2);
            result = {std::to_string(std::stoll(firstNewStone)), std::to_string(std::stoll(secondNewStone))};
            return result;
        }
        long long stonell = std::stoll(stone);
        stonell *= 2024;
        result.emplace_back(std::to_string(stonell));
        return result;
    }

    void printAsteroids(const std::vector<std::string> &asteroids) {
        for (const auto &asteroid : asteroids) {
            std::cout << asteroid << " ";
        }
        std::cout << std::endl;
    }

    std::pair<std::string, long long> Day11::solutionA() {
        const std::vector<std::string> input = readInput(inputALocation);
        std::vector<std::string> asteroids = split(input[0], " ");
        constexpr int iterations = 5;

        std::vector<std::string> newAsteroids;
        newAsteroids.reserve(asteroids.size() * 2);
        for (int i = 0; i < iterations; ++i) {
            for (const auto &asteroid : asteroids) {
                std::vector<std::string> result = applyRule(asteroid);
                newAsteroids.push_back(result[0]);
                if (result.size() == 2) {
                    newAsteroids.push_back(result[1]);
                }
            }
            asteroids = newAsteroids;
            newAsteroids = {};
            newAsteroids.reserve(asteroids.size() * 2);
        }

        return std::make_pair("day 11a", asteroids.size());
    }

    std::map<std::string, long long> countAsteroids(const std::vector<std::string> &asteroids) {
        std::map<std::string, long long> asteroidCount;
        for (auto &asteroid : asteroids) {
            auto match = asteroidCount.find(asteroid);
            if (match == asteroidCount.end()) {
                asteroidCount.insert(std::make_pair<std::string, long long>(asteroid.data(), 1L));
            } else {
                match->second += 1;
            }
        }
        return asteroidCount;
    }

    long long newAsteroidGroupSumDFS(int iterationsLeft, const std::vector<std::string> &asteroids) {
        long long sum = 0;
        auto asteroidCopy = asteroids;
        std::map<std::string, long long> asteroidCount;
        for (auto &asteroid : asteroidCopy) {
            auto match = asteroidCount.find(asteroid);
            if (match == asteroidCount.end()) {
                asteroidCount.insert(std::make_pair<std::string, long long>(std::move(asteroid), 1L));
            } else {
                match->second += 1;
            }
        }
        for (const auto &asteroid : asteroidCount) {
            sum += asteroid.second * countAsteroidsAfterIterationsDFS(asteroid.first, iterationsLeft);
        }
        return sum;
    }

    long long countAsteroidsAfterIterationsDFS(const std::string &asteroid, int iterationsLeft) {
        long long sum = 0;

        if (iterationsLeft == 0) return 1;
        if (iterationsLeft >= 4 && asteroid == "0") {
            sum += newAsteroidGroupSumDFS(iterationsLeft - 4, {"2", "0", "2", "4"});
        } else if (iterationsLeft >= 3 && asteroid == "1") {
            sum += newAsteroidGroupSumDFS(iterationsLeft - 3, {"2", "0", "2", "4"});
        } else if (iterationsLeft >= 3 && asteroid == "2") {
            sum += newAsteroidGroupSumDFS(iterationsLeft - 3, {"4", "0", "4", "8"});
        } else if (iterationsLeft >= 3 && asteroid == "3") {
            sum += newAsteroidGroupSumDFS(iterationsLeft - 3, {"6", "0", "7", "2"});
        } else if (iterationsLeft >= 3 && asteroid == "4") {
            sum += newAsteroidGroupSumDFS(iterationsLeft - 3, {"8", "0", "9", "6"});
        } else if (iterationsLeft >= 5 && asteroid == "5") {
            sum += newAsteroidGroupSumDFS(iterationsLeft - 5, {"2", "0", "4", "8", "2", "8", "8", "0"});
        } else if (iterationsLeft >= 5 && asteroid == "6") {
            sum += newAsteroidGroupSumDFS(iterationsLeft - 5, {"2", "4", "5", "7", "9", "4", "5", "6"});
        } else if (iterationsLeft >= 5 && asteroid == "7") {
            sum += newAsteroidGroupSumDFS(iterationsLeft - 5, {"2", "8", "6", "7", "6", "0", "3", "2"});
        } else if (iterationsLeft >= 8 && asteroid == "8") {
            sum += newAsteroidGroupSumDFS(iterationsLeft - 8, {"6", "0", "7", "2", "4", "0", "4", "8", "2876", "6032", "2876", "6032", "4", "0", "4", "8", "2457", "9456", "32", "77", "26", "8"});
        } else if (iterationsLeft >= 5 && asteroid == "9") {
            sum += newAsteroidGroupSumDFS(iterationsLeft - 5, {"3", "6", "8", "6", "9", "1", "8", "4"});
        } else {
            const auto newAsteroids = applyRule(asteroid);
            for (const auto &newAsteroid : newAsteroids) {
                sum += countAsteroidsAfterIterationsDFS(newAsteroid, iterationsLeft - 1);
            }
        }
        return sum;
    }

    long long countAsteroidsAfterIterationsBFS(const std::vector<std::string> &asteroids, int iterationsLeft) {
        auto asteroidCount = countAsteroids(asteroids);
        std::map<std::string, long long> newAsteroidCount;
        for (int i = 0; i < iterationsLeft; i++) {
            for (const auto &originalAsteroid : asteroidCount) {
                auto result = applyRule(originalAsteroid.first);
                for (const auto &newAsteroid : result) {
                    auto match = newAsteroidCount.find(newAsteroid);
                    if (match != newAsteroidCount.end()) {
                        match->second += originalAsteroid.second;
                    } else {
                        long long c = originalAsteroid.second;
                        newAsteroidCount.insert(std::make_pair<std::string, long long>(newAsteroid.data(), std::move(c)));
                    }
                }
            }
            asteroidCount = newAsteroidCount;
            newAsteroidCount = {};
        }

        long long sum = 0;
        for (const auto &asteroid : asteroidCount) {
            sum += asteroid.second;
        }
        return sum;
    }

    std::pair<std::string, long long> Day11::solutionB() {
        const std::vector<std::string> input = readInput(inputBLocation);
        std::vector<std::string> asteroids = split(input[0], " ");
        printAsteroids(asteroids);

        // long long sum = 0;
        // for (const auto &asteroid : asteroids) {
        //     constexpr int iterations = 40;
        //     sum += countAsteroidsAfterIterationsDFS(asteroid, iterations);
        // }
        long long sum = countAsteroidsAfterIterationsBFS(asteroids, 75);

        return std::make_pair("day 11a", sum);
    }

} // Day11