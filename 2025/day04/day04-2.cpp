#include <iostream>
#include <fstream>
#include <vector>

typedef std::vector<std::vector<bool>> Grid;

int width, height;

int remove(Grid const &in, Grid &out) {
    int total = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (in[y][x]) {
                int x1 = std::max(0, x - 1);
                int y1 = std::max(0, y - 1);
                int x2 = std::min(width - 1, x + 1);
                int y2 = std::min(height - 1, y + 1);
                
                int neighbors = 0;                
                for (int cy = y1; cy <= y2; cy++) {
                    for (int cx = x1; cx <= x2; cx++) {
                        if ((cx != x || cy != y) && in[cy][cx]) {
                            neighbors++;
                        }
                    } 
                }
                if (neighbors < 4) {
                    out[y][x] = false;
                    total++;
                } else {
                    out[y][x] = true;
                }
            } else {
                out[y][x] = false;
            }
        }
    }

    return total;
}
 
int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2025/day04/input.txt");

    if (file.is_open()) {
        Grid in, out;

        while (getline(file, line)) {
            std::vector<bool> row;
            for (auto& c : line) {
                row.emplace_back(c == '@');
            }
            in.emplace_back(row);
            out.emplace_back(row);
        }
        file.close();
        
        width = in[0].size();
        height = in.size();
        
        int total = 0;
        int removed = -1;
        while (removed != 0) {
            removed = remove(in, out);
            total += removed;

            for (int y = 0; y < height; y++) {
                in[y] = out[y];
            }            
        }
        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

