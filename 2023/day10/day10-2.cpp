#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <cstring>
#include <unordered_map>

const int WIDTH = 140;
const int HEIGHT = 140;

std::vector<std::string> map;

struct Vector {
    int x, y;
};
Vector start;

bool loop[HEIGHT][WIDTH];
int xStart[HEIGHT], xEnd[HEIGHT];
int yStart, yEnd;

std::unordered_map<char, std::vector<Vector>> segments {
    {'|', {Vector{ 0, -1}, Vector{ 0,  1}}},
    {'-', {Vector{-1,  0}, Vector{ 1,  0}}},
    {'L', {Vector{ 1,  0}, Vector{ 0, -1}}},
    {'J', {Vector{-1,  0}, Vector{ 0, -1}}},
    {'7', {Vector{-1,  0}, Vector{ 0,  1}}},
    {'F', {Vector{ 1,  0}, Vector{ 0,  1}}}
};

void findStart() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (map[y][x] == 'S') {
                start.x = x;
                start.y = y;
            }
        }
    }
    
    bool u = std::string("|7F").find(map[start.y - 1][start.x]) != std::string::npos;
    bool d = std::string("|LJ").find(map[start.y + 1][start.x]) != std::string::npos;
    bool l = std::string("-LF").find(map[start.y][start.x] - 1) != std::string::npos;
    bool r = std::string("-7J").find(map[start.y][start.x] + 1) != std::string::npos;
    
    if (u && d) { map[start.y][start.x] = '|'; }
    if (l && r) { map[start.y][start.x] = '-'; }
    if (u && r) { map[start.y][start.x] = 'L'; }
    if (u && l) { map[start.y][start.x] = 'J'; }
    if (d && l) { map[start.y][start.x] = '7'; }
    if (d && r) { map[start.y][start.x] = 'F'; }
}

void traceLoop() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            loop[y][x] = false;
        }
        xStart[y] = WIDTH;
        xEnd[y] = 0;
    }
    yStart = HEIGHT;
    yEnd = 0;
    
    Vector current = start;
    Vector prev = current;

    bool done = false;
    while (!done) {
        char c = map[current.y][current.x];
        Vector delta = segments.at(c)[0];
        
        if (current.x + delta.x == prev.x && current.y + delta.y == prev.y) {
            delta = segments.at(c)[1];
        }
        prev = current;
        current.x += delta.x;
        current.y += delta.y;
        
        if (current.x == start.x && current.y == start.y) {
            done = true;
        }

        loop[current.y][current.x] = true;
        
        xStart[current.y] = std::min(xStart[current.y], current.x);
        xEnd[current.y] = std::max(xEnd[current.y], current.x);
        yStart = std::min(yStart, current.y);
        yEnd = std::max(yEnd, current.y);
    }
}

int countInterior() {
    int count = 0;
    
    for (int y = yStart + 1; y <= yEnd; y++) {
        for (int x = xStart[y] + 1; x <= xEnd[y]; x++) {
            if (!loop[y][x]) {
                int pipeCount = 0;
                for (int tx = xStart[y]; tx < x; tx++) {
                    if (loop[y][tx]) {
                        if (map[y][tx] == '|' || map[y][tx] == 'J' || map[y][tx] == 'L') {
                            pipeCount++;
                        }
                    }
                }
                if (pipeCount % 2 != 0) {
                    count++;
                }
            }
        }
    }
    
    return count;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2023/day10/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            map.push_back(line);
        }
        file.close();

        findStart();
        traceLoop();
        
        int count = countInterior();
        std::cout << count << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}

