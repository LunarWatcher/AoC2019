#ifndef DAY1_HPP
#define DAY1_HPP
#include "Day.hpp"
#include "string"
#include <algorithm>
#include <numeric>
#include <iostream>
#include "ExplicitOverloads.hpp"
#include <cmath>

namespace lunarwatcher {

class Day1 : public Day<int> {
public:
    Day1() : Day(1, overloads::stoi) {
        
    }

    int internalPartA() {  
        return std::accumulate(this->rawInput.begin(), this->rawInput.end(), 
                0, [](int a, int b) { return a + std::floor(b / 3.0) - 2; });
    }

    void partA() override {
        std::cout << "Part A: " 
            << internalPartA() 
            << std::endl;
    }

    void partB() override {
        int fuel = 0;
        for (int& moduleMass : rawInput) {
            int moduleFuel = std::floor(moduleMass / 3.0) - 2;
            int cache = moduleFuel;
            while (true) {
                int fuelFuelRequirement = std::floor(cache / 3.0) - 2;
                if (fuelFuelRequirement <= 0)
                    break;
                moduleFuel += fuelFuelRequirement;
                cache = fuelFuelRequirement;
            } 
            fuel += moduleFuel;
        }
        std::cout << "Part B: " << fuel << std::endl;
    }
};

}

#endif
