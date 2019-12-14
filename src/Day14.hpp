#ifndef DAY14_HPP
#define DAY14_HPP

#include "Day.hpp"
#include <map>
#include <sstream>
#include <unordered_map>
#include <algorithm>

namespace lunarwatcher {

class Graph {
public:
    std::map<std::string, long long> dependencies; 
    long long prodCount;
 
    Graph() {
        // Required for maps - SHOULD NOT BE USED!
    }
    Graph(std::map<std::string, long long> dependencies, int prodCount) 
        : dependencies(dependencies), prodCount(prodCount) {  }

};

static inline void makeGraph(std::map<std::string, Graph>& graph, const std::string& line) {
 
    std::istringstream ss(line);
    std::string token;
    
    bool useInput = true;
    size_t pos;
    
    std::string inputStr;
    long long inputInt; 
    
    std::map<std::string, long long> map;
    
    while(ss>>token) {
        while ((pos=token.rfind(',')) != std::string::npos) {
            token.erase(pos, 1);
        }
        
        if (token == "=>") {
            useInput = false;
            continue;   
        }
        auto sub = token[0] - '0';
        if (sub >= 0 && sub <= 9) {
            inputInt = std::stoi(token);
        } else {
            inputStr = token;
            if (useInput) map[inputStr] = inputInt;
        }
    }

    graph[inputStr] = Graph{ map, inputInt };
    
}

class Day14 : Day {
private:
    std::map<std::string, Graph> map;
public:
    Day14() : Day() {
        map = {};
        
        std::cout << "Running tests..." << std::endl;

        withInput({
            "10 ORE => 10 A",
            "1 ORE => 1 B",
            "7 A, 1 B => 1 C",
            "7 A, 1 C => 1 D",
            "7 A, 1 D => 1 E",
            "7 A, 1 E => 1 FUEL"
        });

        withInput({
            "9 ORE => 2 A",
            "8 ORE => 3 B",
            "7 ORE => 5 C",
            "3 A, 4 B => 1 AB",
            "5 B, 7 C => 1 BC",
            "4 C, 1 A => 1 CA",
            "2 AB, 3 BC, 4 CA => 1 FUEL"
        });

        withInput({
            "157 ORE => 5 NZVS",
            "165 ORE => 6 DCFZ",
            "44 XJWVT, 5 KHKGT, 1 QDVJ, 29 NZVS, 9 GPVTF, 48 HKGWZ => 1 FUEL",
            "12 HKGWZ, 1 GPVTF, 8 PSHF => 9 QDVJ",
            "179 ORE => 7 PSHF",
            "177 ORE => 5 HKGWZ",
            "7 DCFZ, 7 PSHF => 2 XJWVT",
            "165 ORE => 2 GPVTF",
            "3 DCFZ, 7 NZVS, 5 HKGWZ, 10 PSHF => 8 KHKGT"
        });
        std::cout << "Test ended." << std::endl;

        auto input = grabRawInput<std::string>(14);
        withInput(input);
    }

    void withInput(const std::vector<std::string>& input) {
        
        for (auto& line : input) {
            makeGraph(map, line);
        }

        partA();
        partB();

        map.clear();
    }

    bool checkBreak(std::map<std::string, long long>& r) {
        for (auto& [k, v] : r) {
            if (k != "ORE" && v > 0)
                return true;
        }

        return false;
    }

    std::map<std::string, long long> reduce(const std::string& ore, long long amount, std::map<std::string, long long>& surplus) {
        auto& graph = map[ore];
        long long units = graph.prodCount;
        if (units == 0)
            throw std::runtime_error("Failed: units == 0");
        long long multiples = std::ceil(amount / double(units));
        surplus[ore] = surplus[ore] + multiples * units - amount;

        std::map<std::string, long long> needed = {};

        for (auto& [ore, count] : graph.dependencies) {
            long long total = count * multiples;
            long long usable = std::min(total, surplus[ore]);
            if (usable != 0) {
                total -= usable;
                surplus[ore] = surplus[ore] - usable;
            }
            needed[ore] = needed[ore] + total;
        }

        return needed;
    }
    

    long long getMinFuel(long long fuel = 1) {

        std::map<std::string, long long> requiredResources = {
            {"FUEL", fuel}
        };
        std::map<std::string, long long> surplus = {};

        while(checkBreak(requiredResources)) {
            for (auto& [ore, count] : requiredResources) {
                if (ore == "ORE" || count == 0) continue;
                auto components = reduce(ore, count, surplus);

                for (auto& [dependency, depCount] : components) { 
                    requiredResources[dependency] = requiredResources[dependency] + depCount;

                }
                count = 0;
 
            }
        }
        return requiredResources["ORE"];
    }

    long long bsearch(long long low, long long high) {
        while (high - low > 1) {
            long long val = low + (high - low) / 2;
            auto fuelForValue = getMinFuel(val);
            if (fuelForValue > 1e12)
                high = val;
            else low = val;
        }

        return low;
    }

    void partA(bool partB = false) override {

        std::cout << "Part A: " << getMinFuel() << std::endl;
    }

    void partB() override {
        std::cout << "Part B: " << bsearch(0, 1e12) << std::endl;
    }

};

}

#endif 
