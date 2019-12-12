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
        std::cout << "Yeah, no." << std::endl 
            << "My intcode implementation has a flaw somewhere and I can't fix it because I have zero tests to verify with, " 
            << "And it works on all other tests I know of. Henlo edge cases - you killed the calendar last year, and now you're back." << std::endl 
            << "I can't magically create tests for this either, because this isn't a pure intcode challenge. I don't know where it goes wrong, "
            << "so I can't create a focused test to pinpoint that one piece of shit bug that causes a bad result for part B." << std::endl 
            << "I barely managed to pull off part A, but it does _not_ like it when the input is 1. It manages to get opcode 67 (num 367) at i = 0, "
            << "which isn't a valid opcode. I have no idea what kind of black magic the intcode class performs - I'm surprised it works at all. "
            << "A memory allocation flaw killed off my computer code while I worked on this day. I had to remove it and just stick the resize "
            << "to true (AKA allocating 1e8 for the vector) because a resize somewhere else just doesn't work!" << std::endl 
            << "There's probably a reasonable explanation, but I can't leech off other people either. If you figure it out, good for you! " 
            << "But I'm tired and frustrated by these intcode challenges. My bad implementation causes this day to fail, and I have 0 chance of fixing it." << std::endl
            << "Days being dependent on your performance on other days is probably going to make further intcode challenges undoable, because I have no idea where I'm "
            << "going wrong, nor do I have any way of verifying. So, fuck this, fuck intcode, and happy holidays, reader of this randomly placed mini-rant";
        throw "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
        // partA(true);
    }
};

}

#endif 
