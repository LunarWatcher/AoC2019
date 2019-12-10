#ifndef DAY6_HPP
#define DAY6_HPP

#include "Day.hpp"
#include <map>
#include <optional>
#include "utils/StdAugments.hpp"

namespace lunarwatcher {

class Day6 : Day {
private:
    // <grav, std::vector<sattelites>>
    std::map<std::string, std::vector<std::string>> universe;

public:
    Day6() : Day() {
        std::vector<std::string> rawInput = this->grabRawInput<std::string>(6);   
        for (std::string& line : rawInput) {

            std::string grav = substring(line, 0, 3);
            std::string satellite = substring(line, 4, 7);
            universe[satellite].push_back(grav);
        }
        partA();
        partB();
    }
    std::vector<std::string> recursiveClusterfuckVector(const std::string& source) {
        std::vector<std::string> traversal;
        std::vector<std::string>& neighbors = universe[source];
        if (neighbors.size() != 0) {
            traversal.insert(traversal.end(), neighbors.begin(), neighbors.end());
        }
        for (const auto& neighbor : neighbors) {
            auto result = recursiveClusterfuckVector(neighbor);
            if (result.size() != 0) {
                traversal.insert(traversal.end(), result.begin(), result.end());
            }
        }

        return traversal;
    }

    unsigned int recursiveClusterfuck(const std::string& checkConnectionsFrom) {
        unsigned int score = 0;
        
        std::vector<std::string>& neighbors = universe[checkConnectionsFrom];
        score += neighbors.size();

        for (std::string& neighbor : neighbors) {
            score += recursiveClusterfuck(neighbor);
        }
        return score;
    }

    void partA(bool = false) override {
        unsigned int score = 0;
        for (auto& [key, vec] : universe) {
            score += recursiveClusterfuck(key);
        }

        std::cout << "Part A: " << score << std::endl;
    }

    void partB() override {
        auto vecA = recursiveClusterfuckVector("YOU");
        auto vecB = recursiveClusterfuckVector("SAN"); // SANta

        for (unsigned long long i = 0; i < vecA.size(); i++) {
            std::string des = vecA[i];
            auto itb = std::find(vecB.begin(), vecB.end(), des);
            if (itb != vecB.end()) {
                int idx = std::distance(vecB.begin(), itb);
                std::cout << "Part B: " << (i + idx) << std::endl; 
                break;
            }
        }
    }

};

}

#endif 
