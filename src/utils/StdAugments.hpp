#ifndef STDAUGMENTS_HPP
#define STDAUGMENTS_HPP

#include <string>
#include <vector>

namespace lunarwatcher {

inline std::string substring(const std::string& str, int startIdx, int endIdx) {
    return str.substr(startIdx, endIdx - startIdx);
}

std::vector<std::pair<int, int>> getSides(const std::pair<int, int>& source) {
    return {{source.first, source.second + 1},
            {source.first, source.second - 1},
            {source.first + 1, source.second},
            {source.first - 1, source.second}};
}

}  // namespace lunarwatcher

#endif
