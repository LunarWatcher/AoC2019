#ifndef INTCOMPUTER_HPP
#define INTCOMPUTER_HPP

#include <vector>
#include <cmath>
#include <utility>
#include <iostream>

namespace lunarwatcher {

class MemScope {
public:
    std::vector<int> baseCode;
    long long diagCode = -1;
    int inputCode;
    int lastInput = 0;
    bool givenPhase = false;
    unsigned long long instructionPointer = 0;
    bool stopped = false;
    MemScope(const std::vector<int>& val, int inputCode, int initInp) 
        : baseCode(val), inputCode(inputCode), lastInput(initInp) {}


};

class IntComputer {
private:
    int get(std::vector<int>& codes, int param, int mode) {
        if (mode == 0)
            return codes[codes[param]];
        else if (mode == 1)
            return codes[param];
        else throw "Unknown mode";
    }
public:
    typedef unsigned long long ullong;

    int amplifiers(std::vector<int>& codes, std::vector<int> ampInput, int initialInput) {
        return amplifiers(codes, ampInput, initialInput, false);
    }

    
    int amplifiers(std::vector<int>& codes, std::vector<int> ampInput, int initialInput, bool feedbackLoop = false) {
        
        std::vector<MemScope> memory; 
        for (auto& inp : ampInput) {
            memory.push_back(MemScope(codes, inp, initialInput));
        }

        do {
            
            for (ullong i = 0; i < memory.size(); i++) {
                auto& scope = memory[i];
                processVector(scope, feedbackLoop);
                if (feedbackLoop && scope.stopped) {
                    return memory[4].diagCode;
                }
                memory[(i + 1) % 5].lastInput = scope.diagCode; 
            }

        } while(feedbackLoop);

        return memory[4].diagCode;
    }

    void processVector(const std::vector<int>& codes, int input) {
        MemScope scope(codes, input, input);
        processVector(scope);  
        
        std::cout << "[IntPuter] Code 4: " << scope.diagCode << std::endl;
    }

    void processVector(MemScope& scope, bool feedbackLoop = false) {
        auto& codes = scope.baseCode;

        ullong& i = scope.instructionPointer;
        bool& givenPhase = scope.givenPhase;
        int diagCode = -1;
        while (i < codes.size()) {
            int instruction = codes[i];
            int opcode;
            // mode, param
            std::vector<std::pair<int, int>> params; 
            
            opcode = instruction % 100;
            int modA = (instruction / 100) % 10;
            int modB = (instruction / 1000) % 10;
            int modC = (instruction / 10000) % 10;

            if (opcode == 1 || opcode == 2) {
                int num1, num2, dest;

                num1 = get(codes, ++i, modA);
                num2 = get(codes, ++i, modB);
                dest = get(codes, ++i, 1);

                if (opcode == 1) {
                    codes[dest] = num1 + num2;
                } else {
                    codes[dest] = num1 * num2;
                }
            } else if (opcode == 3) {
                i++;
                int dest = codes[i];
                if (!givenPhase) {
                    givenPhase = true;
                    codes[dest] = scope.inputCode;
                } else {
                    codes[dest] = scope.lastInput;
                }
            } else if(opcode == 4) {
                i++;
                int source = codes[i];
                diagCode = codes[source];
                scope.diagCode = diagCode;
                if (feedbackLoop) {
                    i++;
                    return;
                }
            } else if (opcode == 5 || opcode == 6) {
                int num1 = get(codes, ++i, modA);
                
                if ((opcode == 5 && num1 != 0) || (opcode == 6 && num1 == 0)) {
                    int num2 = get(codes, ++i, modB);
                    i = num2;
                    continue;
                } else i++;
            } else if (opcode == 7) {
                int num1 = get(codes, ++i, modA);
                int num2 = get(codes, ++i, modB);
                int r = num1 < num2;
                int num3 = get(codes, ++i, 1);
                codes[num3] = r;
            } else if (opcode == 8) {
                int num1 = get(codes, ++i, modA);
                int num2 = get(codes, ++i, modB);
                int r = num1 == num2;
                int num3 = get(codes, ++i, 1);
                codes[num3] = r;
            } else if (opcode == 99) {
                scope.stopped = true;
                return;
            } else {
                std::cout << "ERROR: at i = " << i << ", opcode " << opcode << ", num" << instruction << std::endl;
                return;
            }
            i++;
        }
        throw "Reached the end without code 99";
    }
};

}

#endif 
