#ifndef DAY4_HPP
#define DAY4_HPP

#include "Day.hpp"
#include <algorithm>
#include <map>

namespace lunarwatcher {
    
class Day4 : Day {
private:
    static inline int min = 145852;
    static inline int max = 616942;

    static inline std::string validation = "([0-9])\\1";
    std::vector<std::string> aCombos;
public:
    Day4() : Day() {
        partA();
        partB();
    }

    void partA(bool = false) override {
        for (int i = min; i < max; i++) {
            std::string num = std::to_string(i);
            // Base validation 
            bool hasAdj = false;
            char last = num[0];
            char curr;
            for (unsigned long long j = 1; j < num.length(); j++) {
                curr = num[j];
                if (curr < last) {
                    hasAdj = false;
                    break;
                } else if (!hasAdj && curr == last) {
                    hasAdj = true;
                }
                last = curr;
            }
            if(hasAdj) {
                aCombos.push_back(num);
            }
        }

        std::cout << "Part A: " << aCombos.size() << std::endl;
    }

    void partB() override {
        int combos = 0;

        for (auto& combo : aCombos) {
            std::map<char, int> mMap;
            for (char& c : combo) {
                mMap[c] = mMap[c] + 1;
            }
            for (auto& [k, v] : mMap) 
                if (v == 2){
                    combos++;
                    break;
                }
        } 

        std::cout << "Part B: " << combos << std::endl;
    }
};

}

#endif 
