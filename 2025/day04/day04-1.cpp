#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2025/day04/input.txt");

    if (file.is_open()) {
        std::vector<std::string> grid;
        while (getline(file, line)) {
            grid.emplace_back(line);
        }
        file.close();
        
        int width = grid[0].length();
        int height = grid.size();
        int total = 0;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (grid[y][x] == '@') {
                    int x1 = std::max(0, x - 1);
                    int y1 = std::max(0, y - 1);
                    int x2 = std::min(width - 1, x + 1);
                    int y2 = std::min(height - 1, y + 1);
                    
                    int neighbors = 0;                
                    for (int cy = y1; cy <= y2; cy++) {
                        for (int cx = x1; cx <= x2; cx++) {
                            if ((cx != x || cy != y) && grid[cy][cx] == '@') {
                                neighbors++;
                            }
                        } 
                    }
                    if (neighbors < 4) {
                        total++;
                    }
                }
            }
        }
        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

