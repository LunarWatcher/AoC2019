#ifndef STDAUGMENTS_HPP
#define STDAUGMENTS_HPP
#include <string>

namespace lunarwatcher{

inline std::string substring(const std::string& str, int startIdx, int endIdx) {
    return str.substr(startIdx, endIdx - startIdx);
}

}

#endif 
