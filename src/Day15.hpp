#ifndef DAY15_HPP
#define DAY15_HPP

#include "Day.hpp"
#include "utils/IntComputer.hpp"
#include <map>
#include <stdexcept>
#include <random>

namespace lunarwatcher {

namespace D15 {

enum class TileType {
    OPEN = 0, WALL = 1, OXYGEN = 2
 };

enum class Direction {
    NORTH = 1, SOUTH = 2, WEST = 3, EAST = 4

};
std::pair<int, int> modify(int dir, const std::pair<int, int>& old) {
    switch (dir) {
        case 1:
            return {old.first, old.second + 1};
        case 2: return {old.first, old.second - 1};
        case 3: return {old.first - 1, old.second};
        case 4: return {old.first + 1, old.second};
        default: throw std::runtime_error("That's no moon!");
    }
}


Direction operator!(const Direction& d) {
    if (d == Direction::NORTH) 
        return Direction::SOUTH;
    else if (d == Direction::SOUTH)
        return Direction::NORTH;
    else if (d == Direction::EAST)
        return Direction::WEST;
    else return Direction::EAST;
}


}

class Day15 : Day {
private:
    typedefs::Vector code;
    IntComputer compuper; 
    std::map<std::pair<int, int>, D15::TileType> map; 
    void recordPos(const std::pair<int, int>& pos, const D15::Direction& direction, int legal) {
        map[
        {
                pos.first + (direction == D15::Direction::WEST ? -1 : (direction == D15::Direction::EAST ? 1 : 0)),
            pos.second + (direction == D15::Direction::NORTH ? 1 : (direction == D15::Direction::SOUTH ? -1 : 0))
        }] = legal == 0 ? D15::TileType::WALL : (legal == 1 ? D15::TileType::OPEN : D15::TileType::OXYGEN); 
    }

   
    D15::Direction random(const std::pair<int, int>& pos) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> rand(1, 4);

        //for (int i = 1; i <= 4; i++) {
            //auto nearby = D15::modify(i, pos);
            //if(map.find(nearby) == map.end()) {
                //return (D15::Direction) i;
            //}
        //}
        int random = rand(gen);
        D15::Direction direction = (D15::Direction) random;
        return direction;
    }

    std::vector<std::pair<int, int>> getNearby(const std::pair<int, int>& source) {
        std::vector<std::pair<int, int>> raw;

        for (int i = 1; i <= 4; i++) {
            auto pos = D15::modify(i, source);
            if(map.find(pos) == map.end())
                continue;
            else if (map[pos] == D15::TileType::WALL)
                continue;
            raw.push_back(pos);
        }
        return raw;
    }
    int dijkstra(std::pair<int, int> target) {
        static std::pair<int, int> NULL_PAIR(-3333, -3333);

        std::vector<std::pair<int, int>> visited;
        std::vector<std::pair<int, int>> unvisited;

        std::map<std::pair<int, int>, std::pair<int, std::pair<int, int>>> dists;

        std::pair<int, int> currPos(0, 0);
        dists[currPos] = {0, NULL_PAIR};

        while (true) {
            auto nearby = getNearby(currPos);
            if (nearby.size() == 0) {
                throw std::runtime_error("can't have zero neighbors!");
            }

            for (const auto& pos : nearby) {
                if (std::find(visited.begin(), visited.end(), pos) == visited.end()
                        && std::find(unvisited.begin(), unvisited.end(), pos) == unvisited.end()) {
                    unvisited.push_back(pos);
                    int dist = dists[currPos].first + 1;
                    if (dists.find(pos) == dists.end() || dist < dists[pos].first)
                        dists[pos] = std::make_pair(dist, currPos);

                }
            }

            auto unv = std::find(unvisited.begin(), unvisited.end(), currPos);
            if (unv != unvisited.end())
                unvisited.erase(unv);

            visited.push_back(currPos);
            
            if (currPos == target) {
                auto prePos = dists[target];
                std::vector<std::pair<int, int>> route = {target};

                while (prePos.second != NULL_PAIR) {
                    
                    route.push_back(prePos.second);
                    prePos = dists[prePos.second];

                }

                return route.size() - 1;
            }
            if (unvisited.size() == 0)
                return -3;
            std::sort(unvisited.begin(), unvisited.end(), [dists](std::pair<int, int>& one, std::pair<int, int>& two) mutable -> bool {
                return dists[one].first < dists[two].first;
            });
            currPos = unvisited[0];
        }
        return -3;
    }

    void dumpMap() {

        for (int y = -40; y <= 40; y++) {
            for (int x = -30; x <= 30; x++) {
                std::pair<int, int> pos(x, y);
                if (map.find(pos) == map.end())
                    std::cout << " ";
                else {
                    switch (map[pos]) {
                        case D15::TileType::OPEN: 
                            std::cout << ".";
                            break;
                        case D15::TileType::WALL:
                            std::cout << "#";
                            break;
                        default:
                            std::cout << "O";
                            break;

                    }
                }
            }
            std::cout << std::endl;
        }
    }
public:
    Day15() : Day() {
        code = this->grabCommaSeparatedLongLongs(15);

        partA();
        map.clear();
        partB();
    }

    void partA(bool partB = false) override {
        static std::pair<int, int> oxygen;
        map.clear();

        MemScope scope(code, 0, 0, true);
        scope.givenPhase = true;
        std::pair<int, int> pos(0, 0);
        map[pos] = D15::TileType::OPEN;
        D15::Direction direction = D15::Direction::NORTH;
        bool hasOxygen = false;
        while (true) {
            scope.lastInput = int(direction);

            compuper.processVector(scope, true); 
            int response = scope.diagCode; 
            this->recordPos(pos, direction, response); 

            if (response == 1 || response == 2) {
                switch (direction) {
                case D15::Direction::NORTH:
                    pos.second++;
                    break;
                case D15::Direction::SOUTH:
                    pos.second--;
                    break;
                case D15::Direction::EAST:
                    pos.first++;
                    break;
                case D15::Direction::WEST:
                    pos.first--;
                    break;
                default:
                    throw std::runtime_error("Nope.");
                }
            }
            if (!partB && response == 2) {
                std::cout << "Part A at " << pos.first << "," << pos.second << std::endl;
                std::cout << "Part A: " << dijkstra(pos) << std::endl;

                oxygen = pos;
                return;
            }
            direction = random(pos);
            if (partB && response == 2) {


                int count = 0;
                for (auto& [k, v] : map) {
                    if (v != D15::TileType::WALL) {
                        for (int d = 1; d <= 4; d++) {
                            auto rp = D15::modify(d, k);
                            if(map.find(rp) == map.end()) {
                                count++;

                            } 
                            
                        }
                    }
                }
                if(count == 0) {
                    int minutes = 0;
                    dumpMap(); 
                    auto pos = oxygen;
                    
                    std::vector<std::pair<int, int>> points;
                    points.push_back(pos);
                    int generatedByLast = 1; 
                    while (true) {
                        int gbl = 0;
                        for (int i = 0; i < generatedByLast; i++) {
                            auto point = points[i];
                            std::vector<std::pair<int, int>> neighbors = getNearby(point); 
                            for (auto nearby : neighbors) {
                                if (map.find(nearby) != map.end() && map[nearby] == D15::TileType::OPEN) {
                                    gbl++;
                                    points.push_back(nearby);
                                    map[nearby] = D15::TileType::OXYGEN;
                                }
                            }
                        }

                        points.erase(points.begin(), points.begin() + generatedByLast);
                        generatedByLast = gbl;
                        if (points.size() == 0) break;
                        minutes++;
                    }


                    std::cout << "Part B: " << minutes << std::endl;
    
                    return;

                }
            
            }

        }
    }

    void partB() override {
        partA(true);
    }

};

}

#endif 
