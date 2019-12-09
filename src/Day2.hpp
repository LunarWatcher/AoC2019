#ifndef DAY2_HPP
#define DAY2_HPP
#include "Day.hpp"

namespace lunarwatcher {

class Day2 : Day {
private:
    std::vector<int> rawInput; 
    int part1 = -1;
public:
    Day2() : Day() {
        rawInput = grabCommaSeparatedInts(2);
        partA();
        partB();
    }

    int internalPartA(int a = 12, int b = 2) {
        auto rawInput = this->rawInput;
        
        rawInput[1] = a;
        rawInput[2] = b;

        for (unsigned long long i = 0; i < rawInput.size(); i += 4) {
            int op = rawInput[i];
            if (op == 99) break;
            int idx1 = rawInput[i + 1];
            int idx2 = rawInput[i + 2];
            int storeIdx = rawInput[i + 3];
            if (op == 1){
                rawInput[storeIdx] = rawInput[idx1] + rawInput[idx2];
            } else {
                rawInput[storeIdx] = rawInput[idx1] * rawInput[idx2];
            }
        } 
        return rawInput[0];
    }
    
    void dump(int a, int b) {
        std::cout << "Part B: " << 100 * a + b << std::endl;
    }

    void partA() override {

        part1 = internalPartA();
        std::cout << "Part A: " << part1 << std::endl;
    }
    
    void partB() override {
        int target = 19690720;

        int a = 12, b = 2;
        int currB = b;
        int maxValue = rawInput.size() - 1;
        while (a <= maxValue) {
            while (currB <= maxValue) {
                int cVal = internalPartA(a, currB);
                if (cVal == target) {
                    dump(a, currB);
                    return;
                }
                currB++;
            }
            currB = b;
            a++;
        }
    }

};

}
#endif 
