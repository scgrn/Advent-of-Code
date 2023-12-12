#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>

std::vector<std::string> input;
int width, height;
char map[140][140];

void parseInput() {
    for (int y = 0; y < 140; y++) {
        for (int x = 0; x < 140; x++) {
            map[y][x] = input[y][x];
        }
    }
}

int64_t measurePath() {
    return 0;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2023/day10/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            input.push_back(line);
        }
        file.close();

        parseInput();

        std::cout << measurePath() << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}

