#ifndef DAY_HPP
#define DAY_HPP

#include <functional>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

namespace lunarwatcher {

class Day {
public:
    Day() {}
    virtual ~Day() {}

    template <typename T>
    std::vector<T> grabRawInput(int day, std::function<T(const std::string&)> parser = 0) {
        std::vector<T> rawInput;
        if (!std::is_same<T, std::string>() && !parser)
            throw "Parser can't be null when T != std::string";
        std::ifstream file("input/day" + std::to_string(day) + ".txt");
        std::string cache;
        while (std::getline(file, cache)) {
            rawInput.push_back(parser(cache));
        }
        return rawInput;
    }

    std::vector<int> grabCommaSeparatedInts(int day) {
        std::vector<int> numbers;
        std::ifstream file("input/day" + std::to_string(day) + ".txt");
        std::string cache;
        while (std::getline(file, cache)) {
            std::stringstream stream(cache);
            for (int i; stream >> i;) {
                numbers.push_back(i);
                if (stream.peek() == ',')
                    stream.ignore();
            }
        }
        return numbers;
    }
    /**
     * @param partB    Some days build off code from part A. For these, a switch can be used to separate the two where there's a noticeable difference
     */
    virtual void partA(bool partB = false) = 0;
    virtual void partB() = 0;
};

template <> std::vector<std::string> Day::grabRawInput<std::string>(int day, std::function<std::string(const std::string&)> parser) {
    std::vector<std::string> rawInput;
    std::ifstream file("input/day" + std::to_string(day) + ".txt");
    std::string cache;
    while (std::getline(file, cache)) {
        if (parser)
            rawInput.push_back(parser(cache));
        else
            rawInput.push_back(cache);
    }
    return rawInput;
}

}  // namespace lunarwatcher

#endif
