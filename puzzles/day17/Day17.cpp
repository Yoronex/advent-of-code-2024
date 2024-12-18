//
// Created by Roy on 17/12/2024.
//

#include "Day17.h"

#include <iostream>

namespace Day17 {

    enum Instructions {
        ADV = 0,
        BXL = 1,
        BST = 2,
        JNZ = 3,
        BXC = 4,
        OUT = 5,
        BDV = 6,
        CDV = 7,
    };

    long long getComboOperand(const int operand, const long long registerA, const long long registerB, const long long registerC) {
        if (operand <= 3) return operand;
        if (operand == 4) return registerA;
        if (operand == 5) return registerB;
        if (operand == 6) return registerC;
        std::cout << "Program invalid: reading operand 7" << std::endl;
        throw;
    }

    bool runProgram(const std::vector<int> &program, const long long registerAValue, const long long registerBValue, const long long registerCValue, const std::vector<int> &desiredOutput) {
        long long registerA = registerAValue;
        long long registerB = registerBValue;
        long long registerC = registerCValue;
        int instructionPointer = 0;

        std::vector<int> output;

        while (instructionPointer < program.size()) {
            const int opcode = program[instructionPointer];
            const int operand = program[instructionPointer + 1];
            switch (opcode) {
                case Instructions::ADV: {
                    const long long denominator = getComboOperand(operand, registerA, registerB, registerC);
                    registerA = registerA >> denominator;
                    instructionPointer += 2;
                    break;
                }
                case Instructions::BXL: {
                    registerB = registerB ^ operand;
                    instructionPointer += 2;
                    break;
                }
                case Instructions::BST: {
                    const long long comboOperand = getComboOperand(operand, registerA, registerB, registerC);
                    registerB = comboOperand % 8;
                    instructionPointer += 2;
                    break;
                }
                case Instructions::JNZ: {
                    if (registerA > 0) {
                        instructionPointer = operand;
                    } else {
                        instructionPointer += 2;
                    }
                    break;
                }
                case Instructions::BXC: {
                    registerB = registerB ^ registerC;
                    instructionPointer += 2;
                    break;
                }
                case Instructions::OUT: {
                    const long long comboOperand = getComboOperand(operand, registerA, registerB, registerC);
                    const int toOutput = comboOperand % 8;

                    if (desiredOutput[output.size()] != toOutput) return false;

                    output.push_back(toOutput);
                    instructionPointer += 2;
                    break;
                }
                case Instructions::BDV: {
                    const long long denominator = getComboOperand(operand, registerA, registerB, registerC);
                    registerB = registerA >> denominator;
                    instructionPointer += 2;
                    break;
                }
                case Instructions::CDV: {
                    const long long denominator = getComboOperand(operand, registerA, registerB, registerC);
                    registerC = registerA >> denominator;
                    instructionPointer += 2;
                    break;
                }
            }
        }

        return true;
    }

    std::pair<std::string, long long> Day17::solutionA() {
        const std::vector<std::string> input = readInput(inputALocation);
        const std::string inputRegisterA = split(input[0], ": ")[1];
        const std::string inputRegisterB = split(input[1], ": ")[1];
        const std::string inputRegisterC = split(input[2], ": ")[1];

        const std::vector<std::string> rawProgram = split(split(input[4], ": ")[1], ",");
        std::vector<int> program;
        program.reserve(rawProgram.size());
        for (const auto &p : rawProgram) {
            program.push_back(std::stoi(p));
        }

        long long registerA = std::stoll(inputRegisterA);
        long long registerB = std::stoll(inputRegisterB);
        long long registerC = std::stoll(inputRegisterC);
        int instructionPointer = 0;

        std::vector<int> output;
        while (instructionPointer < program.size()) {
            const int opcode = program[instructionPointer];
            const int operand = program[instructionPointer + 1];
            switch (opcode) {
                case Instructions::ADV: {
                    const long long denominator = getComboOperand(operand, registerA, registerB, registerC);
                    registerA = registerA >> denominator;
                    instructionPointer += 2;
                    break;
                }
                case Instructions::BXL: {
                    registerB = registerB ^ operand;
                    instructionPointer += 2;
                    break;
                }
                case Instructions::BST: {
                    const long long comboOperand = getComboOperand(operand, registerA, registerB, registerC);
                    registerB = comboOperand % 8;
                    instructionPointer += 2;
                    break;
                }
                case Instructions::JNZ: {
                    if (registerA > 0) {
                        instructionPointer = operand;
                    } else {
                        instructionPointer += 2;
                    }
                    break;
                }
                case Instructions::BXC: {
                    registerB = registerB ^ registerC;
                    instructionPointer += 2;
                    break;
                }
                case Instructions::OUT: {
                    const long long comboOperand = getComboOperand(operand, registerA, registerB, registerC);
                    const int toOutput = comboOperand % 8;
                    output.push_back(toOutput);
                    instructionPointer += 2;
                    break;
                }
                case Instructions::BDV: {
                    const long long denominator = getComboOperand(operand, registerA, registerB, registerC);
                    registerB = registerA >> denominator;
                    instructionPointer += 2;
                    break;
                }
                case Instructions::CDV: {
                    const long long denominator = getComboOperand(operand, registerA, registerB, registerC);
                    registerC = registerA >> denominator;
                    instructionPointer += 2;
                    break;
                }
            }
        }

        std::cout << "output: ";
        for (const auto o : output) {
            std::cout << o << ",";
        }
        std::cout << std::endl;

        return std::make_pair("day 17a", 0);
    }

    std::pair<std::string, long long> Day17::solutionB() {
        const std::vector<std::string> input = readInput(inputALocation);
        const std::string inputRegisterA = split(input[0], ": ")[1];
        const std::string inputRegisterB = split(input[1], ": ")[1];
        const std::string inputRegisterC = split(input[2], ": ")[1];

        const std::string rawProgramString = split(input[4], ": ")[1];
        const std::vector<std::string> rawProgram = split(rawProgramString, ",");
        std::vector<int> program;
        program.reserve(rawProgram.size());
        for (const auto &p : rawProgram) {
            program.push_back(std::stoi(p));
        }

        long long registerA = std::stoll(inputRegisterA);
        long long registerB = std::stoll(inputRegisterB);
        long long registerC = std::stoll(inputRegisterC);

        long long i = 0;
        bool correct = runProgram(program, registerA, registerB, registerC, program);
        while (true) {
            if (correct) break;
            registerA++;
            i++;
            correct = runProgram(program, registerA, registerB, registerC, program);

            if (i % 10000000 == 0) {
                std::cout << i << std::endl;
            }
        }

        // std::cout << outputString << std::endl;

        return std::make_pair("day 17b", registerA);
    }

} // Day17