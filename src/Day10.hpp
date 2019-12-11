#ifndef DAY10_HPP
#define DAY10_HPP
#include "Day.hpp"
#include <map>
#include <cmath>

#define PI 3.1415926535897932385626433832795028841971693993751058209749445923078164062862089986280348253421170679821

namespace lunarwatcher {

class Day10 : Day {
private:
    double DEG = PI / 180;
    int WIDTH, HEIGHT;
    static const inline int TWIDTH = 1, 
                 THEIGHT = 1;
    static const inline double sideDist = 0.5; 
    std::vector<std::vector<bool>> map;
    std::vector<std::pair<int, int>> astroTerds;
public: 

    Day10() : Day() {
        auto raw = this->grabRawInput<std::string>(10); 
        HEIGHT = raw.size();
        WIDTH = raw[0].size();
        map.resize(WIDTH);
        for (auto& v : map) {
            v.resize(HEIGHT);
        }
        for (int y = 0; y < raw.size(); y++) {
            auto& row = raw[y];
            for (int x = 0; x < row.length(); x++) {
                map[x][y] = row[x] == '#';
                if (row[x] == '#') {
                    astroTerds.push_back(std::make_pair(x, y));
                }
            }
        }
    }

    void partA(bool = false) override {

        using std::cos;
        using std::sin;
        using std::tan;
        
        std::vector<int, int> optimal;
        int visible = -99;

        for (auto& pos : astroTerds) {
            double angle = 0;
            int& x = pos.first;
            int& y = pos.second;
            std::vector<std::pair<int, int>> hits; 
            int px = x;
            int py = y;
            while (angle < 2*PI) {

                float dy = 0;
                float dx = 0; 

                float rayDirX = cos(angle); 
                float rayDirY = sin(angle);

                // playerMapPos = x/y
                // playerWorldPos = playerMapPos // only used for width/height transforms 
                 
                
                double deltaDistX = std::abs(1 / rayDirX);
                double deltaDistY = std::abs(1 / rayDirY);

                double wallDist; 
                int stepX, stepY;

                double sideDistX, sideDistY; 
                if (rayDirX < 0) {
                    stepX = -1;
                } else {
                    stepX = 1;
                }
                if (rayDirY < 0)
                    stepY = -1;
                else stepY = 1;

                sideDistX = sideDistY = 0.5; // we're roughly in the middle 

                while (true) {
                    if (sideDistX < sideDistY) {
                        sideDistX += deltaDistX;
                        px += stepX;
                    } else {
                        sideDistY += deltaDistY;
                        py += stepY;
                    }

                    if (this->map[px][py] > 0) {
                        if (px == x && py == y) {
                            continue;
                        } else if (std::find(hits.begin(), hits.end(), pos) == hits.end()){
                            hits.push_back(pos);
                            break;
                        }
                    }
                }

                angle += DEG / 2;
            }
            
            if (hits.size() > visible) {
                visible = hits.size();
                optimal = pos;
            }
        } 
    }

    void partB() override {

    }
};
    
}

#endif 
