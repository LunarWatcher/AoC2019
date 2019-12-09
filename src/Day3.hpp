#ifndef DAY3_HPP
#define DAY3_HPP

#include "Day.hpp"
#include <map>
#include <sstream>
#include <utility>
#include <algorithm>
#include <optional>
namespace lunarwatcher {

struct Point { int x, y; };

bool between(int x, int left, int right) {
    return std::min(left, right) < x && x < std::max(left, right);
}
int manhatten(Point a, Point b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}
int manhatten(Point pos) {
    return std::abs(pos.x) + std::abs(pos.y);
}

class Day3 : public Day {
private:
    static inline Point origin = {0, 0};

    std::vector<std::pair<Point, Point>> wire1;
    std::vector<std::pair<Point, Point>> wire2;
public:
    Day3() : Day() {
        std::vector<std::string> rawCoords = grabRawInput<std::string>(3);
        int x = 0, y = 0;
        // There's two wires of input 

        bool p = false;
        for (const auto& wire : rawCoords) {
            std::istringstream stream(wire);
            std::string pos;
            Point lastPoint = { 0, 0};

            while (std::getline(stream, pos, ',')) {

                char dir = pos[0];
                int count = std::stoi(pos.substr(1));
                if (dir == 'L')
                    x -= count;
                else if (dir == 'R')
                    x += count;
                else if (dir == 'U') 
                    y += count;
                else y -= count;
                Point point = {x, y};
                if (!p)
                    wire1.push_back({lastPoint, point});
                else wire2.push_back({lastPoint, point});
                lastPoint = point;
            }
            p = true;
            x = y = 0;
        }

        partA();
        partB();
    }

    std::optional<Point> intersects(std::pair<Point, Point> w1, std::pair<Point, Point> w2) {

        if (between(w1.first.x, w2.first.x, w2.second.x)
                && between (w2.first.y, w1.first.y, w1.second.y)) {
            Point pos = {w1.first.x, w2.second.y};
            return pos;
        } else if (between(w2.first.x, w1.first.x, w1.second.x) 
                && between (w1.first.y, w2.first.y, w2.second.y)) {
            Point pos = {w2.first.x, w1.second.y};
            return pos;
        }
        return {};
    }

    void partA(bool = false) override {
        int minDist = 9999999;
        int minSteps = 9999999;
        int step1 = 0;
        for (auto& w1 : wire1) {
            int step2 = 0;
            for (auto& w2 : wire2) {

                auto pos = intersects(w1, w2);
                if (pos) {
                    int dist = manhatten(*pos);
                    if (dist < minDist)
                        minDist = dist;
                    int steps = step1 + step2 + manhatten(*pos, w1.first) + manhatten(*pos, w2.first);
                    if (steps < minSteps)
                        minSteps = steps;
                }
                step2 += manhatten(w2.first, w2.second);
            }
            step1 += manhatten(w1.first, w1.second);
        }
        std::cout << "Part A: " << minDist << std::endl;
        std::cout << "Part B: " << minSteps << std::endl;
    }

    void partB() override {
        // Unused
    }
};

}

#endif 
