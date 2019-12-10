#ifndef DAY9_HPP
#define DAY9_HPP

#include "Day.hpp"
#include "utils/IntComputer.hpp"

namespace lunarwatcher {

class Day9 : Day {
private:
    typedefs::Vector codes; 
    IntComputer computer;
public:
    Day9() : Day() {
        std::cout << "Running tests." << std::endl << "Test 1 part A: " << std::endl;
        codes = { 109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99 };
        partA();
        std::cout << "Running second test" << std::endl;
        codes = { 1102,34915192,34915192,7,4,7,99,0 };
        partA();
        std::cout << "Running test 3" << std::endl;
        codes = {104,1125899906842624,99};
        partA();
        std::cout << "Running test 4" << std::endl;
        codes = {203, 1, 4, 4, 99};
        partA();
        std::cout << "Testing done." << std::endl;
        codes = this->grabCommaSeparatedLongLongs(9);

        partA();
        partB();
    }

    void partA(bool = false) override {
        std::cout << "Part A: " << std::endl;
        computer.processVector(codes, 1, true);
    }

    void partB() override {
        std::cout << "Part B: " << std::endl;
        computer.processVector(codes, 2, true);
    }
};

}

#endif 
