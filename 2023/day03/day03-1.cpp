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

void findPotentialParts(int y) {
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

bool isSymbol(char c) {
    return !(std::isdigit(c) || c == '.');
}

bool isPartValid(Part part) {
    int xStart = std::max(part.x - 1, 0);
    int xEnd = std::min(part.x + (int)part.number.length(), SCHEMATIC_SIZE - 1);
    
    if (part.y > 0) {
        for (int x = xStart; x <= xEnd; x++) {
            if (isSymbol(schematic[part.y - 1][x])) {
                return true;
            }
        }
    }

    if (isSymbol(schematic[part.y][xStart])) {
        return true;
    }
    if (isSymbol(schematic[part.y][xEnd])) {
        return true;
    }

    if (part.y < SCHEMATIC_SIZE - 1) {
        for (int x = xStart; x <= xEnd; x++) {
            if (isSymbol(schematic[part.y + 1][x])) {
                return true;
            }
        }
    }

    return false;
}

int sumValidParts() {
    int sum = 0;
    for (auto part : parts) {
        if (isPartValid(part)) {
            sum += atoi(part.number.c_str());
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
            findPotentialParts(index);
            index++;
        }
        file.close();
    }
    std::cout << sumValidParts() << std::endl;
    
    return 0;
}

