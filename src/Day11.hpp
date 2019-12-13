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
            std::cout << "Painted: " << painted.size();
            auto minElement 
                = *std::min_element(painted.begin(), painted.end(),
                        [](auto& a, auto& b) {
                            return a.first < b.first
                                    && a.second < b.second;
                        });
            auto maxElement = *std::min_element(painted.begin(), painted.end(), 
                    [](auto& a, auto& b) {
                        return a.first > b.first 
                                && a.second > b.second;
                    });

            int minX = minElement.first,
                minY = minElement.second,
                maxX = maxElement.first,
                maxY = maxElement.second;
        
            for (int y = minY; y <= maxY; y++) {
                auto pos = std::make_pair(0, y);
                for (int x = minX; x <= maxX; x++) {
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
