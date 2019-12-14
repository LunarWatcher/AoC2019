#ifndef INTCOMPUTER_HPP
#define INTCOMPUTER_HPP

#include <vector>
#include <cmath>
#include <utility>
#include <iostream>

namespace lunarwatcher {

namespace typedefs {
    typedef std::vector<long long> Vector;
}

class MemScope {
public:
    typedefs::Vector baseCode;
    long long diagCode = -1;
    int inputCode;
    int lastInput = 0;
    bool givenPhase = false;
    unsigned long long instructionPointer = 0;
    long long relativeBase = 0;
    bool stopped = false;
    bool print = false;

    MemScope(const typedefs::Vector& val, int inputCode, int initInp, bool resize = false) 
        : baseCode(val), inputCode(inputCode), lastInput(initInp) {
        if (resize)
            baseCode.resize(10000000);
    }


};

class IntComputer {
private:
    long long get(typedefs::Vector& codes, long long param, long long mode, long long node) {

        if (mode == 0)
            return codes[codes[param]];
        else if (mode == 1)
            return codes[param];
        else if (mode == 2)
            return codes[codes[param] + node];
        else throw "Unknown mode";
    }

    long long getTarget(typedefs::Vector& codes, long long param, long long mode, long long node) {

        if (mode == 0)
            return codes[param];
        else if (mode == 2)
            return codes[param] + node;
        else throw "Fuck you";

    }
    void put(typedefs::Vector& codes, long long dest, int mode, long long node, long long value) {
        if (mode == 0)
            codes[dest] = value;
        else if (mode == 2)
            codes[dest + node] = value;
        else throw "Unknown/unsupported mode";
    }
public:
    typedef unsigned long long ullong;

    int convertMode(int mode) {
        if (mode == 1 || mode == 2)
            return mode;
        else return 1;
    }

    int amplifiers(typedefs::Vector& codes, std::vector<int> ampInput, int initialInput) {
        return amplifiers(codes, ampInput, initialInput, false);
    }

    
    int amplifiers(typedefs::Vector& codes, std::vector<int> ampInput, int initialInput, bool feedbackLoop = false) {
        
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

    void processVector(const typedefs::Vector& codes, int input, bool resize = false) {
        MemScope scope(codes, input, input, resize);
        scope.print = true;
        
        processVector(scope, false);  
        
    }


    void processVector(MemScope& scope, bool feedbackLoop = false) {
        auto& codes = scope.baseCode;

        ullong& i = scope.instructionPointer;
        long long& relativeBase = scope.relativeBase;

        bool& givenPhase = scope.givenPhase;
        while (true) {
            
            long long instruction = codes[i];
            int opcode;
            // mode, param
            std::vector<std::pair<int, int>> params; 
            
            opcode = instruction % 100;
            int modA = (instruction / 100) % 10;
            int modB = (instruction / 1000) % 10;
            int modC = (instruction / 10000) % 10;

            if (opcode == 1 || opcode == 2) {
                long long num1, num2, dest;

                num1 = get(codes, ++i, modA, relativeBase);
                num2 = get(codes, ++i, modB, relativeBase);
                dest = getTarget(codes, ++i, modC, relativeBase);
                if (opcode == 1) {
                    //put(codes, dest, modC, relativeBase, num1 + num2);
                    codes[dest] = num1 + num2;
                } else {
                    //put(codes, dest, modC, relativeBase, num1 * num2);
                    codes[dest] = num1 * num2;
                }
            } else if (opcode == 3) {
                long long dest = getTarget(codes, ++i, modA, relativeBase);
                if (!givenPhase) {
                    givenPhase = true;
                    //put(codes, dest, modA, relativeBase, scope.inputCode);
                    codes[dest] = scope.inputCode;
                } else {
                    //put (codes, dest, modA, relativeBase, scope.lastInput);
                    codes[dest] = scope.lastInput;
                }
            } else if(opcode == 4) {
                long long diagCode = get(codes, ++i, modA, relativeBase);
                
                scope.diagCode = diagCode;
                if (scope.print)
                    std::cout << "[IntPuter] Code 4: " << scope.diagCode << std::endl;
                
                if (feedbackLoop) {
                    i++;
                    return;
                }
            } else if (opcode == 5 || opcode == 6) {
                long long num1 = get(codes, ++i, modA, relativeBase);
                
                if ((opcode == 5 && num1 != 0) || (opcode == 6 && num1 == 0)) {
                    long long num2 = get(codes, ++i, modB, relativeBase);
                    i = num2;
                    continue;
                } else i++;
            } else if (opcode == 7) {
                long long num1 = get(codes, ++i, modA, relativeBase);
                long long num2 = get(codes, ++i, modB, relativeBase);
                long long r = num1 < num2;
                long long num3 = getTarget(codes, ++i, modC, relativeBase);
                // put(codes, num3, modC, relativeBase, r);
                codes[num3] = r;
            } else if (opcode == 8) {
                long long num1 = get(codes, ++i, modA, relativeBase);
                long long num2 = get(codes, ++i, modB, relativeBase);
                long long r = num1 == num2;
                long long num3 = getTarget(codes, ++i, modC, relativeBase);
                
                //put(codes, num3, modC, relativeBase, r);
                codes[num3] = r;
            } else if (opcode == 9) {
                long long num1 = get(codes, ++i, modA, relativeBase);
                relativeBase += num1;
            } else if (opcode == 99) {
                scope.stopped = true;
                return;
            } else {
                std::cout << "ERROR: at i = " << i << ", opcode " << opcode << ", num" << instruction << std::endl;
                throw "ERR";
            }
            i++;
        }
    }
};

}

#endif 
