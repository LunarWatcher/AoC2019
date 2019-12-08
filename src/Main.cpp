#include <iostream>
#include <string>
#include "Day1.hpp"
#include "Day2.hpp"

int main(int argc, char** argv) {
    int day = -1;
    
    if (argc == 2)
        day = std::atoi(argv[1]);
    else { 
        std::cout << "Enter day: ";
        std::cin >> day;
    }

    switch(day) {
    case 1:
        { lunarwatcher::Day1 exec; }
        break;
    case 2:
        { lunarwatcher::Day2 exec; }
        break;
    default:
        std::cerr << "Day not supported or implemented: " << day << std::endl;
        return -2;
    }


}

