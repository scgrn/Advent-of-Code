#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>

struct Vertex {
    int64_t x, y;
};

std::vector<std::string> input;
std::vector<Vertex> trench;
uint64_t perimeter = 0;

void parseInput() {
    int64_t x = 0;
    int64_t y = 0;
    
    for (auto& line : input) {
        const std::string dirs = "RDLU";
        
        char dir;
        int64_t steps;
        std::string color;

        std::stringstream ss(line);
        ss >> dir;
        ss >> steps;
        ss >> color;

        steps = stol(color.substr(2, 5), nullptr, 16);
        dir = dirs[(int)color[7] - '0'];
                 
        perimeter += steps;
        
        switch (dir) {
            case 'U': y -= steps; break;
            case 'D': y += steps; break;
            case 'L': x -= steps; break;
            case 'R': x += steps; break;
            default: break;
        };
        
        trench.push_back(Vertex {x, y});
    }
}

//  shoelace formula
int64_t calculateArea() {
    int64_t area = 0;
    
    int n = trench.size();
    int j = n - 1;
    for (int i = 0; i < n; i++) {
        area += (trench[j].x + trench[i].x) * (trench[j].y - trench[i].y); 
        j = i;
    }
    
    if (area < 0) {
        area = -area;
    }
    
    return area / 2;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2023/day18/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            input.push_back(line);
        }
        file.close();

        parseInput();
        int64_t area = calculateArea();
        
        //  pick's theorem
        std::cout << area + (perimeter / 2) + 1 << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}

