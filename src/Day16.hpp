#ifndef DAY16_HPP
#define DAY16_HPP

#include "Day.hpp"

namespace lunarwatcher {

class Day16 : Day {
private:
    std::string input;
    std::vector<int> inputVec;
    std::vector<int> positions;
public:
    Day16() : Day() {
        std::cout << "Running test..." << std::endl;
        this->inputVec = {8, 0, 8, 7, 1, 2, 2, 4, 5, 8, 5, 9, 1, 4, 5, 4, 6, 6, 1, 9, 0, 8, 3, 2, 1, 8, 6, 4, 5, 5, 9, 5 };
        partA();
        std::cout << "Test complete.\n";
        this->input = grabRawInput<std::string>(
                //160
                16
            
            )[0];
        inputVec.clear();
        for(const auto& chr : input) {
            if (chr == '\r')
                continue;
            int num = chr - '0';
            inputVec.push_back(num);
        }

        for (int i = 0; i < 7; i++) 
            positions.push_back(inputVec.at(i));

        std::vector<int> original = this->inputVec;
        partA();
        this->inputVec = original;
        partB();
    }

    int getPattern(int relPtr, int row) {
        static std::vector<int> basePattern = {0, 1, 0, -1};
        int ptr = (relPtr + 1) / (row + 1);
        int relPos = ptr % 4;
        return basePattern[relPos];
    }

    void partA(bool partB = false) override {
        std::vector<int> inputVec(this->inputVec);
        for (int i = 0; i < 100; i++) {
            std::vector<int> copy(inputVec);
            for (int row = 0; row < inputVec.size(); row++) {
                long long sum = 0;
                for (int j = 0; j < copy.size(); j++) {
                    sum += ((long long) getPattern(j, row)) * ((long long) copy[j]);
                }
                inputVec[row] = (int) std::abs(sum) % 10;

            }

        }
        std::cout << std::endl;

        if(!partB) {
            std::cout << "Part A: ";
            for (int i = 0; i < 8; i++) 
                std::cout << inputVec[i];
            std::cout << std::endl;
        } else {
            std::cout << "Part B: ";
            for (auto& idx : this->positions) {
                std::cout << inputVec[idx];
            }
            std::cout << std::endl;
        }
    }

    void partB() override {
        //std::vector<int> original(inputVec);
        //for (int i = 0; i < 10000; i++) {
            //inputVec.insert(inputVec.end(), original.begin(), original.end());
        //}
        //std::cout << "Starting part B..." << std::endl;
        //partA(true);
        throw std::runtime_error("Yeah, this isn't gonna work. The brute-force approach I had would've had a guesstimated time complexity of O(shitton), and I have no idea how else to solve it. I'll get back to this at some point");
    }
};

}

#endif 
