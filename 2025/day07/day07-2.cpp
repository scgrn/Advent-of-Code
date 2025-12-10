#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

int main(int argc, char* argv[]) {
    std::vector<std::string> input;

    std::string line;
    std::ifstream file("2025/day07/input.txt");

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            input.emplace_back(line);
        }
        file.close();
        
        int w = input[0].length();
        int h = input.size();
        
        std::vector<std::vector<uint64_t>> grid;
        for (int y = 0; y < h; y++) {
            std::vector<uint64_t> row;
            for (int x = 0; x < w; x++) {
                row.emplace_back(0);
            }
            grid.emplace_back(row);
        }

        for (int y = 0; y < h - 1; y++) {
            for (int x = 0; x < w; x++) {
                if (input[y][x] == '|' || input[y][x] == 'S') {
                    if (grid[y][x] == 0) {
                        grid[y][x] = 1;
                    }
                    
                    uint64_t val = grid[y][x];
                    if (input[y + 1][x] == '^') {
                        input[y + 1][x - 1] = '|';
                        input[y + 1][x + 1] = '|';
                        
                        grid[y + 1][x - 1] += val;
                        grid[y + 1][x + 1] += val;
                    } else {
                        input[y + 1][x] = '|';
                        
                        grid[y + 1][x] += val;
                    }
                }
            }
        }

        uint64_t timelines = 0;
        for (int x = 0; x < w; x++) {
            timelines += grid[h - 1][x];
        }
        std::cout << timelines << std::endl;

    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

