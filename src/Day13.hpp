#ifndef DAY13_HPP
#define DAY13_HPP

#include "Day.hpp"
#include "utils/IntComputer.hpp"
#include <map>

namespace lunarwatcher {

class Day13 : Day {
private:
    typedefs::Vector code; 

    IntComputer puter;
    int required = 0, px = 0, bx = 0;
public:
    Day13() : Day() {
        code = this->grabCommaSeparatedLongLongs(13);

        partA();
        partB();
    }
  
    void partA(bool partB = false) override {
        std::map<std::pair<int, int>, int> world = {};
        if (partB)
            code[0] = 2;
        auto memory = MemScope(code, 0, 0, true);
        memory.givenPhase = true;

        int score = 0;

        int paddleX = px;
        int ballX = bx;


        while (!memory.stopped) {
            puter.grabNOutput(memory, 3);
            int x = memory.mOutputs.at(0);
            int y = memory.mOutputs.at(1);
            int tile = memory.mOutputs.at(2);
            if (x == -1 && y == 0)
                score = tile;
            else {
                std::pair<int, int> pos = {x, y};
                world[pos] = tile;

                if (tile == 3) {
                    paddleX = x;
                    if(!partB) 
                        px = x;
                } else if (tile == 4) { 
                    ballX = x;
                    if(!partB)
                        bx = x;
                }

            }
            if (partB) {

                memory.lastInput = (paddleX < ballX ? 1 : (paddleX > ballX ? -1 : 0));

            }
        }
        if(!partB) {
            int c = 0;
            for (auto& [k, v] : world) {
                if (v == 2) c++;
            }
            this->required = c;
            std::cout << "Part A: " << c << std::endl;
        } else {
            std::cout << "Part B: " << score << std::endl;
        }
    }

    void partB() override {
        partA(true);
    }
};

}

#endif 
