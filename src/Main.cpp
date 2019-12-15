#include <iostream>
#include <string>
#include "Day1.hpp"
#include "Day2.hpp"
#include "Day3.hpp"
#include "Day4.hpp"
#include "Day5.hpp"
#include "Day6.hpp"
#include "Day7.hpp"
#include "Day8.hpp"
#include "Day9.hpp"
#include "Day10.hpp"
#include "Day11.hpp"
#include "Day12.hpp"
#include "Day13.hpp"
#include "Day14.hpp"
#include "Day15.hpp"

int main(int argc, char** argv) {
    int day = -1;
    
    if (argc == 2)
        day = std::atoi(argv[1]);
    else { 
        std::cout << "Enter day: ";
        std::cin >> day;
    }
    
    switch(day) {
    case 1: { lunarwatcher::Day1 exec; } break;
    case 2: { lunarwatcher::Day2 exec; } break;
    case 3: { lunarwatcher::Day3 exec; } break;
    case 4: { lunarwatcher::Day4 exec; } break;
    case 5: { lunarwatcher::Day5 exec; } break;
    case 6: { lunarwatcher::Day6 exec; } break;
    case 7: { lunarwatcher::Day7 exec; } break;
    case 8: { lunarwatcher::Day8 exec; } break;
    case 9: { lunarwatcher::Day9 exec; } break;
    case 10: { lunarwatcher::Day10 exec; } break;
    case 11: { lunarwatcher::Day11 exec; } break;
    case 12: { lunarwatcher::Day12 exec; } break;
    case 13: { lunarwatcher::Day13 exec; } break;
    case 14: { lunarwatcher::Day14 exec; } break;
    case 15: { lunarwatcher::Day15 exec; } break;
    default:
        std::cerr << "Day not supported or implemented: " << day << std::endl;
        return -2;
    }


}

