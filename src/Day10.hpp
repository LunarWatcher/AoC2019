#ifndef DAY10_HPP
#define DAY10_HPP
#include "Day.hpp"

#include <cmath>
#include <limits>
#include <algorithm>

#define PI 3.1415926535897932385626433832795028841971693993751058209749445923078164062862089986280348253421170679821

namespace lunarwatcher {

class Day10 : Day {
private:
    int WIDTH, HEIGHT;
    std::vector<std::vector<bool>> map;
    std::vector<std::pair<int, int>> astroTerds;
public:
    typedef std::pair<int, int> Vector2; 

    Day10() : Day(), map() {

        auto raw = this->grabRawInput<std::string>(
                // 100  // Test 1
                // 101 // test 2
                // 102
                // 103
                // 104
                10 // Real input
                ); 
        HEIGHT = raw.size();
        WIDTH = raw[0].size();
        map = std::vector<std::vector<bool>>(WIDTH, std::vector<bool>(HEIGHT));
        for (unsigned long long y = 0; y < raw.size(); y++) {
            std::string& row = raw[y];
            for (unsigned long long x = 0; x < row.length(); x++) {
                map.at(x).at(y) = row.at(x) == '#';
                if (row[x] == '#') {
                    astroTerds.push_back(std::make_pair(x, y));
                }
            }
        }

        std::cout << "Testing parallellization.." << std::endl;

        Vector2 a = {-1, 2};
        Vector2 b = {-1, 2};
        if (!isParallell(a, b)) 
            throw "Fail test one";
        std::cout << "Test one passed" << std::endl;
        Vector2 c = {1, -2};
        if (!isParallell(a, c))
            throw "Fail test 2";
        std::cout << "Test two passed" << std::endl;

        Vector2 d = {3, 19};
        if (isParallell(c, d))
            throw "Fail test 3";

        std::cout << "Test three passed" << std::endl;
        
        Vector2 e = {-3, -19};
        if (!isParallell(d, e))
            throw "Fail test 4";
        
        std::cout << "Test four passed" << std::endl;

        if(isSame(d, e))
            throw "Fail test 5"; 
        std::cout << "Test five passed" << std::endl;
       
        if(!isParallell({3,3},{2,2}))
            throw "ugh";

        std::cout << "henlo" << std::endl;
        if(!isSame({3, 3}, {2, 2}))
            throw "FUCK NO!";

        std::cout << "Testing done"<< std::endl;

        partA();
        partB();
    }

    Vector2 createVector(const Vector2& from, const Vector2& to) { 
        return std::make_pair(to.first - from.first, to.second - from.second); 
    }
    Vector2 addVector(const Vector2& from, const Vector2& to) {
        return std::make_pair(from.first + to.first, to.second + from.second);
    }
    bool isParallell(const Vector2& a, const Vector2& b) {
        if ((a.first == b.first && a.first == 0) || (a.second == b.second && a.second == 0))
            return true;
        else if (a.first == b.second && a.first == 0)
            return false;
        else if (a.second == b.first && a.second == 0)
            return false;
        double k1 = double(a.first) / b.first;
        double k2 = double(a.second) / b.second;
        return k1 == k2;
    }
 
    double len(const Vector2& vec) {
        return std::sqrt(std::pow(vec.first, 2) + std::pow(vec.second, 2));
    }

    double dotProduct (const Vector2& a, const Vector2& b) {
        return a.first * b.first + a.second * b.second;
    }

    int sign(double a) {
        if(a == 0)
            return 1;
        return a / std::abs(a);
    }

    bool doubleComp(double a, double b) {
        double i = a - b;
        if (i < 0)
            i = -i;
        return i < std::numeric_limits<double>::epsilon();
    }

    double getAngle (Vector2& diff) {
        using std::acos;

        static Vector2 x = {0, 1};
        static double vLen = len(x);
        double c = (180.0/PI)*acos(dotProduct(diff, x) / (vLen * len(diff)));
        if (diff.first > 0) {
            return 360 - c;
        }
        return c;
    }

    bool isSame(const Vector2& a, const Vector2& b) {
        if(!isParallell(a, b))
            return false;

        static Vector2 x = {1, 0};
        static double vLen = len(x);
        using std::acos;
        int alpha1 = std::round((180.0/PI)*acos(dotProduct(a, x) / (vLen * len(a))));
        int alpha2 = std::round((180.0/PI)*acos(dotProduct(b, x) / (vLen * len(b))));
        // fun fact: floating point numbers fucking suck. 
        // Rounding to an int and using degrees instead increases accuracy thanks to that (either that or I have a bad comparison implementation)
        // alpha1 != alpha2. From some testing:
        // > 0.785398, 0.785398. Equals? 0
        // Yeah, really. You'd think it's identical, but it's not.  
        if (alpha1 == alpha2) {
            if (alpha1 == 90 || alpha1 == 270) {
                if (sign(a.first) != sign(b.first) || sign(a.second) != sign(b.second))
                    return false;
            }

            return true;
        }
        return false;
    }
    std::pair<int, int> optimal;
    void partA(bool = false) override {
        std::pair<int, int> optimal;
        int max;
        for (auto& pos : astroTerds) {
            int visible = 0;
            std::vector<Vector2> vecs; 
            for (auto& pos2 : astroTerds){
                if (pos == pos2) continue;
                vecs.push_back(createVector(pos2, pos));
            }

            std::vector<Vector2> hits;
            for (auto& vec : vecs) {
                bool unique = true;
                for (auto& vec2 : hits) {
                    if (isSame(vec, vec2)) {
                        unique = false;
                        break;
                    }
                }

                if (unique) {
                    visible++;
                    hits.push_back(vec);
                }
                
            }

            if (visible > max) {
                max = visible;
                optimal = pos;
            }

        }
        this->optimal = optimal;
        std::cout << "Part A: " << max << std::endl;
        std::cout << "At: " << optimal.first << ", " << optimal.second << std::endl;
    }

    void partB() override {
        auto source = optimal;
    
        // Raw vectors to all teh objects
        std::vector<Vector2> vecs;
        std::cout << "Iterating all teh vecs for a time complexity of O(livia)" << std::endl;
        
        for (auto& terd : astroTerds) {
            if (terd == source) continue;
            vecs.push_back(createVector(terd, source));
        }

        std::vector<Vector2> refined;
        std::vector<Vector2> processed;
        for (Vector2& vec : vecs) {
            if (vec == source)
                continue;
            if (std::find(processed.begin(), processed.end(), vec) != processed.end()) 
                continue;

            std::vector<Vector2> matches;
            for (Vector2& otherVec : vecs) {
                if (otherVec == vec) continue;
                if (std::find(matches.begin(), matches.end(), otherVec) == matches.end() && isSame(vec, otherVec)) {
                    matches.push_back(otherVec);
                }
            }

            if (matches.size() == 0) {
                processed.push_back(vec);
                refined.push_back(vec);
                continue;
            }

            std::sort(matches.begin(), matches.end(), [this](const Vector2& a, const Vector2& b) -> bool {
                return this->len(a) < this->len(b);
            });
            refined.push_back(matches[0]);
            processed.insert(processed.end(), matches.begin(), matches.end());

        }

        std::sort(refined.begin(), refined.end(), [this](auto& a, auto& b) -> bool {
            return this->getAngle(a) < this->getAngle(b);
        });
        
        std::cout << "Sanity check: Found " << refined.size() << " astroterds" << std::endl;

        std::cout << "Part B: " << std::endl;
        auto r = addVector({refined[199].first * (refined[199].first < 0 ? 1 : -1), refined[199].second * (refined[199].second > 0 ? -1 : 1)}, source);
        //auto c = std::make_pair(source.first + c.first, source.second + c.second);
        std::cout << r.first << "," << r.second << std::endl;
        std::cout << (r.first * 100 + r.second) << std::endl;
    }
};
    
}

#endif 
