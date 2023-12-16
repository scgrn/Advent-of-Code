#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <unordered_map>

std::vector<std::string> input;
int width, height;

//  GPT-generated custom hash function for std::vector<std::string>
struct VectorHash {
    std::size_t operator() (const std::vector<std::string>& v) const {
        std::hash<std::string> stringHasher;
        std::size_t hash = 0;
        for (const auto& str : v) {
            hash ^= stringHasher(str) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

std::unordered_map<std::vector<std::string>, uint64_t, VectorHash> cache;

void rollN() {
    for (int x = 0; x < width; x++) {
        for (int y = 1; y < height; y++) {
            if (input[y][x] == 'O') {
                int yPos = y;
                while (yPos > 0 && input[yPos - 1][x] == '.') {
                    yPos--;
                }
                input[y][x] = '.';
                input[yPos][x] = 'O';
            }
        }
    }
}

void rollW() {
    for (int y = 0; y < height; y++) {
        for (int x = 1; x < width; x++) {
            if (input[y][x] == 'O') {
                int xPos = x;
                while (xPos > 0 && input[y][xPos - 1] == '.') {
                    xPos--;
                }
                input[y][x] = '.';
                input[y][xPos] = 'O';
            }
        }
    }
}

void rollS() {
    for (int x = 0; x < width; x++) {
        for (int y = height - 2; y >= 0; y--) {
            if (input[y][x] == 'O') {
                int yPos = y;
                while (yPos < height - 1 && input[yPos + 1][x] == '.') {
                    yPos++;
                }
                input[y][x] = '.';
                input[yPos][x] = 'O';
            }
        }
    }
}

void rollE() {
    for (int y = 0; y < height; y++) {
        for (int x = width - 2; x >= 0; x--) {
            if (input[y][x] == 'O') {
                int xPos = x;
                while (xPos < width - 1 && input[y][xPos + 1] == '.') {
                    xPos++;
                }
                input[y][x] = '.';
                input[y][xPos] = 'O';
            }
        }
    }
}

int64_t count() {
    int64_t sum = 0;

    for (int y = 0; y < height; y++) {
        int count = 0;
        for (int x = 0; x < width; x++) {
            if (input[y][x] == 'O') {
                count++;
            }
        }
        sum += (count * (height - y));
    }

    return sum;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2023/day14/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            input.push_back(line);
        }
        file.close();
        
        width = input[0].size();
        height = input.size();

        uint64_t period = 0;
        uint64_t phaseShift = 0;
        int64_t finalIteration = -1;
        const int64_t TARGET_ITERATION = 1000000000;

        for (int64_t i = 0; i < TARGET_ITERATION; i++) {
            rollN();
            rollW();
            rollS();
            rollE();

            if (period == 0 && cache.count(input) > 0) {
                phaseShift = cache.at(input);
                period = i - phaseShift;

                finalIteration = (TARGET_ITERATION - phaseShift) % period + phaseShift + period - 1;
            } else {
                cache.emplace(input, i);
            }

            if (i == finalIteration) {
                break;
            }
        }

        std::cout << count() << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    

    return 0;
}
