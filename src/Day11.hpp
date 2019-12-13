#ifndef DAY11_HPP
#define DAY11_HPP

#include "Day.hpp"
#include "utils/IntComputer.hpp"
#include <map>
#include <algorithm>

namespace lunarwatcher {

enum class Direction {
    UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3
};

class Day11 : Day {
private:
    static constexpr int BLACK = 0, 
                     WHITE = 1;
    IntComputer puter;
    typedefs::Vector codes;

public:
    Day11() : Day() {

        std::cout << "Testing against someone else's input..." << std::endl;
        codes = {
            3,8,1005,8,351,1106,0,11,0,0,0,104,1,104,0,3,8,102,-1,8,10,1001,10,1,10,4,10,108,1,8,10,4,10,102,1,8,28,3,8,1002,8,-1,10,101,1,10,10,4,10,1008,8,0,10,4,10,1002,8,1,51,1006,0,85,2,1109,8,10,3,8,1002,8,-1,10,101,1,10,10,4,10,1008,8,0,10,4,10,102,1,8,80,1,2,2,10,1,1007,19,10,1,1001,13,10,3,8,1002,8,-1,10,1001,10,1,10,4,10,108,1,8,10,4,10,1001,8,0,113,1,2,1,10,1,1109,17,10,1,108,20,10,2,1005,3,10,3,8,102,-1,8,10,1001,10,1,10,4,10,108,1,8,10,4,10,1002,8,1,151,2,5,19,10,1,104,19,10,1,109,3,10,1006,0,78,3,8,102,-1,8,10,1001,10,1,10,4,10,1008,8,0,10,4,10,1002,8,1,189,1006,0,3,2,1004,1,10,3,8,1002,8,-1,10,101,1,10,10,4,10,1008,8,1,10,4,10,1001,8,0,218,1,1008,6,10,1,104,8,10,1006,0,13,3,8,1002,8,-1,10,101,1,10,10,4,10,1008,8,0,10,4,10,102,1,8,251,1006,0,17,1006,0,34,1006,0,24,1006,0,4,3,8,102,-1,8,10,1001,10,1,10,4,10,1008,8,0,10,4,10,102,1,8,285,1006,0,25,2,1103,11,10,1006,0,75,3,8,1002,8,-1,10,1001,10,1,10,4,10,108,1,8,10,4,10,101,0,8,316,2,1002,6,10,1006,0,30,2,106,11,10,1006,0,21,101,1,9,9,1007,9,1072,10,1005,10,15,99,109,673,104,0,104,1,21101,0,937151009684,1,21101,0,368,0,1105,1,472,21102,386979963796,1,1,21102,379,1,0,1106,0,472,3,10,104,0,104,1,3,10,104,0,104,0,3,10,104,0,104,1,3,10,104,0,104,1,3,10,104,0,104,0,3,10,104,0,104,1,21101,179410325723,0,1,21101,426,0,0,1106,0,472,21101,0,179355823195,1,21102,437,1,0,1106,0,472,3,10,104,0,104,0,3,10,104,0,104,0,21101,0,825460785920,1,21101,460,0,0,1105,1,472,21102,1,838429614848,1,21102,1,471,0,1105,1,472,99,109,2,21202,-1,1,1,21102,40,1,2,21102,1,503,3,21101,493,0,0,1105,1,536,109,-2,2106,0,0,0,1,0,0,1,109,2,3,10,204,-1,1001,498,499,514,4,0,1001,498,1,498,108,4,498,10,1006,10,530,1101,0,0,498,109,-2,2106,0,0,0,109,4,2101,0,-1,535,1207,-3,0,10,1006,10,553,21101,0,0,-3,21202,-3,1,1,22101,0,-2,2,21101,0,1,3,21101,572,0,0,1105,1,577,109,-4,2105,1,0,109,5,1207,-3,1,10,1006,10,600,2207,-4,-2,10,1006,10,600,21202,-4,1,-4,1106,0,668,21202,-4,1,1,21201,-3,-1,2,21202,-2,2,3,21102,619,1,0,1105,1,577,22102,1,1,-4,21101,0,1,-1,2207,-4,-2,10,1006,10,638,21101,0,0,-1,22202,-2,-1,-2,2107,0,-3,10,1006,10,660,22101,0,-1,1,21101,660,0,0,106,0,535,21202,-2,-1,-2,22201,-4,-2,-4,109,-5,2105,1,0
        };
        partA();
        partB();
        std::cout << "Test complete" << std::endl;

        codes = this->grabCommaSeparatedLongLongs(11);

        partA();
        partB();
    }

    Direction recomputeDirection(Direction current, int lr) {
        switch (current) {
            case Direction::UP: 
                return lr == 0 ? Direction::LEFT : Direction::RIGHT;
            case Direction::RIGHT:
                return lr == 0 ? Direction::UP : Direction::DOWN;
            case Direction::DOWN:
                return lr == 0 ? Direction::RIGHT : Direction::LEFT;
            case Direction::LEFT:
                return lr == 0 ? Direction::DOWN : Direction::UP;
        }
    }

    void partA (bool partB = false) override {
        std::pair<int, int> pos = {0, 0};
        Direction dir = Direction::UP;
        MemScope scope(codes, -9, partB ? 1 : 0, true);
        scope.givenPhase = true;
        
        std::map<std::pair<int, int>, bool> world;
        world = {};
        std::vector<std::pair<int, int>> visited;
        visited = {};

        while (!scope.stopped) {
            puter.processVector(scope, true);
            int color = scope.diagCode;
            puter.processVector(scope, true);
            int direction = scope.diagCode;
            
            world[pos] = bool(color);

            dir = recomputeDirection(dir, direction);
            switch (dir) {
            case Direction::UP: 
                pos.second--;
                break;
            case Direction::DOWN:
                pos.second++;
                break;
            case Direction::LEFT:
                pos.first--;
                break;
            default:
                pos.first++;
                break;
            }
            if(std::find(visited.begin(), visited.end(), pos) == visited.end())
                visited.push_back(pos);
            scope.lastInput = world[pos];
        }     
        if(!partB)
            std::cout << "Part A: " << visited.size() << std::endl;
        else {
            std::cout << visited.size() << std::endl;
            std::vector<std::pair<int, int>> painted;
            for(auto& [pos, p] : world) {
                if (p) {
                    painted.push_back(pos);
                }
            }
            auto minElement 
                = *std::min_element(painted.begin(), painted.end(),
                        [](auto& a, auto& b) {
                            return a.first < b.first
                                    && a.second < b.second;
                        });

            int minX = minElement.first,
                minY = minElement.second;

            const auto letters = 8;
            const auto width = 4;
            const auto spaceWidth = 2;
            const auto total = letters * width + spaceWidth * 2 + 4;
            for (int y = minY; y <= minY + 6; y++) {
                auto pos = std::make_pair(0, y);
                for (int x = minX; x <= minX + total; x++) {
                    pos.first = x;
                    auto& entry = world[pos];
                    std::cout << (entry ? "#" : " ");
                }

                std::cout << std::endl;
            }

        }


    }

    void partB() override {
         partA(true);
    }
};

}

#endif 
