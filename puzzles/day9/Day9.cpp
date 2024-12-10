//
// Created by Roy on 08/12/2024.
//

#include "Day9.h"

#include <array>
#include <iostream>
#include <set>

namespace Day9 {
    struct MemoryBlock {
        long long position;
        long long length;
        long long id;
    };

    bool operator<(const MemoryBlock &lhs, const MemoryBlock &rhs) {
        if (lhs.position < rhs.position) return true;
        return false;
    }

    void printMemory(const std::set<MemoryBlock> &mem) {
        return;

        int currentPosition = 0;
        for (const auto &block : mem) {
            for (int i = 0; i < block.position - currentPosition; i++) {
                std::cout << ".";
            }
            for (int i = 0; i < block.length; i++) {
                std::cout << block.id;
            }
            currentPosition = block.position + block.length;
        }
        std::cout << std::endl;
    }

    std::pair<std::string, long long> Day9::solutionA() {
        const std::string input = readInput(inputALocation)[0];

        // <Position, Length, ID>
        std::set<MemoryBlock> memoryBlocks;

        long long memoryPosition = 0;
        long long memoryId = 0;
        for (long long i = 0; i < input.size(); i++) {
            int value = std::stoi(input.substr(i, 1));
            if (i % 2 == 0) {
                memoryBlocks.insert({ memoryPosition, value, memoryId });
                memoryId++;
            }
            memoryPosition += value;
        }

        // printMemory(memoryBlocks);

        std::set<MemoryBlock> reorderedMemoryBlocks = memoryBlocks;
        auto previousBlock = memoryBlocks.begin();
        auto currentBlock = ++(memoryBlocks.begin());
        long long currentPosition = previousBlock->position + previousBlock->length;
        long long currentFreeSize = currentBlock->position - currentPosition;
        for (auto itToMove = memoryBlocks.rbegin(); itToMove != memoryBlocks.rend(); ++itToMove) {
            if (currentPosition >= itToMove->position) break;
            long long remainderToMove = itToMove->length;

            while (remainderToMove > 0) {
                // printMemory(reorderedMemoryBlocks);
                const long long toMove = std::min(remainderToMove, currentFreeSize);
                if (toMove > 0) {
                    reorderedMemoryBlocks.insert({ currentPosition, toMove, itToMove->id });
                }
                remainderToMove -= toMove;
                currentPosition += toMove;
                currentFreeSize -= toMove;
                if (currentPosition >= itToMove->position) break;
                if (currentFreeSize == 0) {
                    ++previousBlock;
                    ++currentBlock;
                    currentPosition = previousBlock->position + previousBlock->length;
                    currentFreeSize = currentBlock->position - currentPosition;
                }

            }

            auto currentBlockInReorderedMemory = reorderedMemoryBlocks.find({ itToMove->position });
            if (remainderToMove > 0) {
                const MemoryBlock copy = *currentBlockInReorderedMemory;
                reorderedMemoryBlocks.erase(currentBlockInReorderedMemory);
                reorderedMemoryBlocks.insert({ copy.position, remainderToMove, copy.id });
            } else {
                reorderedMemoryBlocks.erase(currentBlockInReorderedMemory);
            }
        }

        // printMemory(reorderedMemoryBlocks);

        long long sum = 0;
        for (const auto &block : reorderedMemoryBlocks) {
            for (int i = 0; i < block.length; i++) {
                sum += (block.position + i) * block.id;
            }
        }

        return std::make_pair("day 9a", sum);
    }

    std::pair<std::string, long long> Day9::solutionB() {
        const std::string input = readInput(inputBLocation)[0];

        // <Position, Length, ID>
        std::set<MemoryBlock> memoryBlocks;

        long long memoryPosition = 0;
        long long memoryId = 0;
        for (long long i = 0; i < input.size(); i++) {
            long long value = std::stoi(input.substr(i, 1));
            if (i % 2 == 0) {
                memoryBlocks.insert({ memoryPosition, value, memoryId });
                memoryId++;
            }
            memoryPosition += value;
        }

        // printMemory(memoryBlocks);

        std::set<MemoryBlock> reorderedMemoryBlocks = memoryBlocks;
        // auto previousBlock = memoryBlocks.begin();
        // auto currentBlock = ++(memoryBlocks.begin());

        for (auto itToMove = memoryBlocks.rbegin(); itToMove != memoryBlocks.rend(); ++itToMove) {
            for (auto previousBlock = reorderedMemoryBlocks.begin(); std::next(previousBlock) != reorderedMemoryBlocks.end(); ++previousBlock) {
                const auto currentBlock = std::next(previousBlock);
                const long long currentPosition = previousBlock->position + previousBlock->length;
                const long long currentFreeSize = currentBlock->position - currentPosition;

                if (previousBlock->position >= itToMove->position) {
                    break;
                }
                if (itToMove->length <= currentFreeSize) {
                    reorderedMemoryBlocks.insert({ currentPosition, itToMove->length, itToMove->id });
                    const auto currentBlockInReorderedMemory = reorderedMemoryBlocks.find({ itToMove->position });
                    reorderedMemoryBlocks.erase(currentBlockInReorderedMemory);

                    // printMemory(reorderedMemoryBlocks);
                    break;
                }
            }
        }

        // printMemory(reorderedMemoryBlocks);

        long long sum = 0;
        for (const auto &block : reorderedMemoryBlocks) {
            for (long long i = 0; i < block.length; i++) {
                sum += (block.position + i) * block.id;
            }
        }

        return std::make_pair("day 9b", sum);
    }

} // Day9