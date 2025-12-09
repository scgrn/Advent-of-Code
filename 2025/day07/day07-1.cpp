#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2025/day07/input.txt");

    if (file.is_open()) {
        std::vector<std::string> input;
        std::string line;        
        while (getline(file, line)) {
            input.emplace_back(line);
        }

        int w = input[0].length();
        int h = input.size();
        uint64_t splits = 0;
        for (int y = 0; y < h - 1; y++) {
            for (int x = 0; x < w; x++) {
                if (input[y][x] == '|' || input[y][x] == 'S') {
                    if (input[y + 1][x] == '^') {
                        splits++;
                        input[y + 1][x - 1] = '|';
                        input[y + 1][x + 1] = '|';
                    } else {
                        input[y + 1][x] = '|';
                    }
                }
            }
        }
        std::cout << splits << std::endl;
        
        file.close();
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

