#ifndef DAY12_HPP
#define DAY12_HPP

#include "Day.hpp"
#include <memory>
#include <algorithm>
#include <numeric> 

namespace lunarwatcher {

typedef struct Moon {
private:
    static inline int refId = 0;
public:
    long long x, y, z,
        vx = 0, vy = 0, vz = 0;
    int x0, y0, z0;
    const int id;
    bool returned = false;

    Moon(int x, int y, int z) 
        : x(x), y(y), z(z), id(refId++), 
        vx(0), vy(0), vz(0),
        x0(x), y0(y), z0(z) {
    }

    void processVelocities(Moon& other) {
        if (x < other.x) {
            vx++;
            other.vx--;
        } else if (x > other.x) {
            vx--;
            other.vx++;
        }

        if (y < other.y) {
            vy++; other.vy--;
        } else if (y > other.y) {
            vy--; other.vy++;
        }

        if (z < other.z) { 
            vz++; other.vz--;
        } else if (z > other.z) {
            vz--; other.vz++;
        }

    }

    void tick() {
        x += vx;
        y += vy;
        z += vz;

        if (vx == vy && vy == vz && vx == 0) {
            returned = true;
        } else if (returned) returned = false;
    }

    bool operator==(const Moon& other) {
        return other.id == id;
    }

    bool operator==(const Moon& other) const {
        return other.id == id;
    }

    long long getEnergy() {
        return (std::abs(x) + std::abs(y) + std::abs(z)) * (std::abs(vx) + std::abs(vy) + std::abs(vz));
    }
    
    bool reset(int axis) {
        switch (axis) {
            case 0: return vx == 0 && x == x0;
            case 1: return vy == 0 && y == y0;
            default: return vz == 0 && z == z0;
        }
    }

} Moon;

class Day12 : Day {
private:
    std::vector<std::shared_ptr<Moon>> moons;

public:
    Day12() : Day() {
        // This ain't portable, but neither is the input
        moons.push_back(std::make_shared<Moon>(-6, -5, -8));
        moons.push_back(std::make_shared<Moon>(0, -3, -13));
        moons.push_back(std::make_shared<Moon>(-15, 10, -11));
        moons.push_back(std::make_shared<Moon>(-3, -8, 3));
    
        partA();
        partB();
    }

    void partA(bool partB = false) {
        // My code isn't normally this ugly, I swear
        static long long ticks = 1;
        std::cout << ticks << std::endl;
        std::vector<long long> vecNormalize = {0, 0, 0};
        
        // No copy, NO SOUP FOR YOU! 
        // (AKA when you reprocess with 1k ticks less on the second round for part B,
        // you're gonna get the wrong result lmao)
         
        while (true) {
            for (int i = 0; i < moons.size(); i++) {
                if (i == 3)
                    continue;
                for (int j = i + 1; j < moons.size(); j++) {
                    moons[i]->processVelocities(*moons[j]);
                }
            }
            int c = 0;
            for (auto moon : moons) {
                moon->tick();
            }

            if (partB) {
                if (vecNormalize[0] == 0ll 
                        || vecNormalize[1] == 0ll
                        || vecNormalize[2] == 0ll) {
                    for (int i = 0; i < vecNormalize.size(); i++) {
                        if (vecNormalize[i] == 0) {

                            if (moons[0]->reset(i) && moons[1]->reset(i) && moons[2]->reset(i) && moons[3]->reset(i)) {
                                vecNormalize[i] = ticks;
                            }
                        }
                    }
                } else break;
            }
            ticks++; 
            if (ticks == 1001 && !partB)
                break;
        } 
        
        if (!partB) {
            long long energy = 0;
            for (std::shared_ptr<Moon>& moon : moons) {
                energy += moon->getEnergy();
            } 

            std::cout << "Part A: " << energy  << std::endl;
        } else {
            long long cache = 
                std::lcm(vecNormalize[0], std::lcm(vecNormalize[1], vecNormalize[2]));
            std::cout << "Part B: " << cache << std::endl;
        }
    }

    void partB() {
        partA(true);
    }
};

}

#endif 
