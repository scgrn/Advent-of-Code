#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <locale>

const int SCHEMATIC_SIZE = 140;

std::array<std::string, SCHEMATIC_SIZE> schematic;

struct Part {
    int x, y;
    std::string number;
};
std::vector<Part> parts;

void findParts(int y) {
    std::string line = schematic[y];
    bool numeric = false;
    int spanStart = 0;
    for (int x = 0; x < SCHEMATIC_SIZE; x++) {
        if (std::isdigit(line[x])) {
            if (!numeric) {
                spanStart = x;
                numeric = true;
            }
        } else {
            if (numeric) {
                numeric = false;

                Part part;
                part.x = spanStart;
                part.y = y;
                part.number = line.substr(spanStart, (x - spanStart));

                parts.push_back(part);
            }
        }
    }
    if (numeric) {
        Part part;
        part.x = spanStart;
        part.y = y;
        part.number = line.substr(spanStart, (SCHEMATIC_SIZE - spanStart));

        parts.push_back(part);
    }
}

int findSumOfGearRatios() {
    int sum = 0;
    
    for (int y = 0; y < SCHEMATIC_SIZE; y++) {
        for (int x = 0; x < SCHEMATIC_SIZE; x++) {
            if (schematic[y][x] == '*') {
                //  found a potential gear, find all adjacent parts
                std::vector<Part> adjParts;
                
                for (auto part : parts) {
                    if (abs(y - part.y) <= 1) {
                        if (x >= part.x - 1 && x <= part.x + part.number.size()) {
                            adjParts.push_back(part);
                        }
                    }
                }
                
                //  only a valid gear if it is adjacent to exactly two parts
                if (adjParts.size() == 2) {
                    int part1 = atoi(adjParts.at(0).number.c_str());
                    int part2 = atoi(adjParts.at(1).number.c_str());

                    int ratio = part1 * part2;
                    sum += ratio;
                }
            }
        }
    }
    
    return sum;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2023/day03/input.txt");
    if (file.is_open()) {
        int index = 0;
        while (getline(file, line)) {
            schematic[index] = line;
            findParts(index);
            index++;
        }
        file.close();
    }
    
    std::cout << findSumOfGearRatios() << std::endl;
    
    return 0;
}

