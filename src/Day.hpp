#ifndef DAY_HPP
#define DAY_HPP

#include <functional>
#include <string>
#include <vector>
#include <fstream>

namespace lunarwatcher {

template <typename T>
class Day {
protected:
    int day;
    std::vector<T> rawInput;

public:
    Day(int day, std::function<T(const std::string&)> parser = 0) : day(day) {
        if (!std::is_same<T, std::string>() && !parser)
            throw "Parser can't be null when T != std::string";
        grabRawInput(day, parser);
    }
    virtual ~Day() {}

    void grabRawInput(int day, std::function<T(const std::string&)> parser = 0) {
        std::ifstream file("input/day" + std::to_string(day) + ".txt");
        std::string cache;
        while (std::getline(file, cache)) {
            rawInput.push_back(parser(cache));
        }
    }

    virtual void partA() = 0;
    virtual void partB() = 0;
};

template <> void Day<std::string>::grabRawInput(int day, std::function<std::string(const std::string&)> parser) {
    std::ifstream file("input/day" + std::to_string(day) + ".txt");
    std::string cache;
    while (std::getline(file, cache)) {
        if (parser)
            rawInput.push_back(parser(cache));
        else
            rawInput.push_back(cache);
    }
}

}  // namespace lunarwatcher

#endif
