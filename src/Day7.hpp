#ifndef DAY7_HPP
#define DAY7_HPP

#include "utils/IntComputer.hpp"
#include "Day.hpp"
#include <algorithm>

namespace lunarwatcher {


class Day7 : Day {
private:
    IntComputer puter;
    typedefs::Vector codes; 
public:
    Day7() : Day() {

        std::cout << "Running test 1 for part A: " << std::endl;
        codes = {
            3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0
        };
        partA(); 
        if(puter.amplifiers(codes, {4,3,2,1,0}, 0, false) != 43210)
            throw "Bad computer result";
        else 
            std::cout << "Test 1 passed." << std::endl;
        
        codes = {
            3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,
            27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5
        };

        std::cout << "Running test 1 for part B: " << std::endl;
        int res = puter.amplifiers(codes, {9, 8, 7, 6, 5}, 0, true); 
        if (res != 139629729) {
            std::cout << "Found " << res << ", expected 139629729" << std::endl;
            throw "Bad computer result";
        } else 
            std::cout << "Test 1 passed" << std::endl;
        partB();
        std::cout << "Tests done. Running real input" << std::endl;
        

        codes = this->grabCommaSeparatedLongLongs(7);

        partA();
        partB();
    }

    void partA(bool partB = false) override {
        int maxOutput = 0; 
        std::vector<int> digits;
        if (partB) 
            digits = {5, 6, 7, 8, 9};
        else digits = {0, 1, 2, 3, 4};

        do {
            int output = puter.amplifiers(codes, digits, 0, partB);
            if (output > maxOutput) {
                maxOutput = output;
            }
        } while (std::next_permutation(digits.begin(), digits.end()));
        std::cout << "Part " << (partB ? "B: " : "A: ") << maxOutput << std::endl;
    }

    void partB() override {
        partA(true);
    }
};

}

#endif 
