#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <limits>

struct Galaxy {
    int64_t x, y;
};
std::vector<Galaxy> galaxies;
std::vector<std::string> input;

int height, width;

void findGalaxies() {
    height = input.size();
    width = input[0].size();
    
    for (int64_t y = 0; y < height; y++) {
        for (int64_t x = 0; x < width; x++) {
            if (input[y][x] == '#') {
                galaxies.push_back(Galaxy{x, y});
            }
        }
    }
}

void expandUniverse() {
    int64_t xOffset[width];
    int64_t yOffset[height];
    
    int64_t ofs = 0;
    for (int x = 0; x < width; x++) {
        bool found = false;
        for (int y = 0; y < height; y++) {
            if (input[y][x] == '#') {
                found = true;
            }
        }
        
        if (!found) {
            ofs++;
        }
        xOffset[x] = ofs;
    }
    
    ofs = 0;
    for (int y = 0; y < height; y++) {
        bool found = false;
        for (int x = 0; x < width; x++) {
            if (input[y][x] == '#') {
                found = true;
            }
        }
        
        if (!found) {
            ofs++;
        }
        yOffset[y] = ofs;
    }
    
    for (auto& galaxy : galaxies) {
        galaxy.x += xOffset[galaxy.x];
        galaxy.y += yOffset[galaxy.y];
    }
}

int64_t calculateDistances() {
    int64_t sum = 0;
    
    for (int i = 0; i < galaxies.size() - 1; i++) {
        for (int j = i + 1; j < galaxies.size(); j++) {
            int64_t dist = abs(galaxies[i].x - galaxies[j].x) + abs(galaxies[i].y - galaxies[j].y);
            sum += dist;
        }
    }
    
    return sum;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2023/day11/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            input.push_back(line);
        }
        file.close();
        
        findGalaxies();
        expandUniverse();
        
        std::cout << calculateDistances() << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}
