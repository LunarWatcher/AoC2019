#ifndef DAY17_HPP
#define DAY17_HPP

#include "Day.hpp"
#include "utils/IntComputer.hpp"
#include "utils/StdAugments.hpp"

#include <map>

namespace lunarwatcher {

class Day17 : Day {
private:
    typedefs::Vector code;
    IntComputer compshitter;
    std::map<std::pair<int, int>, char> map;
    std::pair<int, int> droidPos;
public:
    Day17() : Day() {
        code = this->grabCommaSeparatedLongLongs(17);
        partA();
        partB();
    }

    void partA(bool = false) override {
        std::pair<int, int> coords(0, 0);
        MemScope scope(code, 0, 0, true);
        std::vector<std::pair<int, int>> intersections = {};
        int yMax = 0, xMax = 0;
        while (!scope.stopped) {
            compshitter.processVector(scope, true);
            long long& response = scope.diagCode;
            switch (response) {
            case 35:
                map[coords] = '#';
                break;
            case 46: 
                map[coords] = '.';
                break;
            case '^':
                map[coords] = '/n';
                break;
            case 10:
                if (coords.first > xMax)
                    xMax = coords.first;
                coords.second++;
                yMax++;
                coords.first = 0;

                continue;
            default:
                map[coords] = (char) response;
            }
            coords.first++;
        }
        long long sum = 0;
        for (auto& [pos, chr] : map) {
            if (chr == '#') {
                for (auto& nPos : getSides(pos)) {
                    if (map[nPos] != '#')
                        goto fail;
                }
                {
                    sum += (pos.first) * (pos.second);
                }
fail:;
            }
        }

        std::cout << "Part A: " << sum << std::endl;

        for (int y = 0; y <= yMax; y++) {
            for (int x = 0; x <= xMax; x++) {
                std::pair<int, int> pos(x, y);
                auto chr = ((map.find(pos) != map.end()) ? map[pos] : ' ');
                std::cout << chr;
            }
            std::cout << std::endl;
        }
        
    }

    void partB() override {

    }

};

}

#endif 

