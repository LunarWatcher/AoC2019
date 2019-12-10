#ifndef DAY5_HPP
#define DAY5_HPP

#include <vector>
#include "Day.hpp"
#include "ExplicitOverloads.hpp"
#include "utils/IntComputer.hpp"

namespace lunarwatcher {

class Day5 : Day {
private:
    typedefs::Vector codes;
    IntComputer computer;

public:
    Day5() : Day(), computer() {
        codes = this->grabCommaSeparatedLongLongs(5);
        partA();
        partB();
    }

    void partA(bool = false) override {
        computer.processVector(codes, 1);
    }

    void partB() override {
        computer.processVector(codes, 5);
    }

};
}

#endif 
