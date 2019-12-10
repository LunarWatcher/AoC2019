#ifndef DAY8_HPP
#define DAY8_HPP

#include "Day.hpp"
#include <algorithm>

namespace lunarwatcher {

class Day8 : Day {
private:
    static inline int WIDTH = 25;
    static inline int HEIGHT = 6;
    std::vector<std::string> layers;
public:
    Day8() : Day() {
        std::string input = this->grabRawInput<std::string>(8)[0];
        int layers = input.length() / (WIDTH * HEIGHT);

        while (input.length() > 0) {
            if (input.length() == 1 && input == "\r")
                break;
            std::string layer = input.substr(0, WIDTH * HEIGHT);
            std::cout << layer << std::endl;
            input = input.substr(WIDTH * HEIGHT);
            this->layers.push_back(layer);
        }
        
        if (this->layers.size() != layers) {
            std::cout << "Invalid size. Expected " << layers << ", found " << this->layers.size() << std::endl;
            throw "FAIL!";
        }
        std::cout << "Found " << layers << " layers." << std::endl;
        partA();
        partB();
    }
    
    void partA(bool = false) override {
        std::string tLayer;
        int count = 9999999;
        for (const std::string layer : layers) {
            int zeroes = std::count(layer.begin(), layer.end(), '0');
            if (zeroes < count) {
                count = zeroes;
                tLayer = layer;
            }
        }

        std::cout << "Part A: " 
            << (std::count(tLayer.begin(), tLayer.end(), '1') * std::count(tLayer.begin(), tLayer.end(), '2'))
            << std::endl;
    }

    void partB() override {
        for (int i = 0; i < WIDTH * HEIGHT; i++) {
            for (auto layer : layers) {

                if (i >= layer.length())
                    throw 332;
                if (layer[i] == '2')
                    continue;
                std::cout << (layer[i] == '1' ? '#' : ((layer[i] == '0') ? ' ' : 'X'));
                break;
            }
            if ((i + 1) % 25 == 0)
                std::cout << std::endl;
        }
        std::cout << std::endl;
        

    }
};

}

#endif 
