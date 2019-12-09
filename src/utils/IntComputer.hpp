#ifndef INTCOMPUTER_HPP
#define INTCOMPUTER_HPP

#include <vector>
#include <cmath>
#include <utility>
#include <iostream>

namespace lunarwatcher {

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

    void processVector(std::vector<int> codes, int input) {
        ullong i = 0;
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
                codes[dest] = input;

            } else if(opcode == 4) {
                i++;
                int source = codes[i];
                std::cout << "[IntPuter] Code 4: " << codes[source] << std::endl;
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
                std::cout << "[IntPuter] HALT!" << std::endl;
                return;
            } else {
                std::cout << "ERROR: at i = " << i << ", opcode " << opcode << ", num" << instruction << std::endl;
                return;
            }
            i++;
        }
    }
};

}

#endif 
