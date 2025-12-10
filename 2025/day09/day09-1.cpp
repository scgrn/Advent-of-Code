#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2025/day09/input.txt");

    struct Tile {
        int64_t x, y;
    };
    std::vector<Tile> tiles;
    
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            int comma = line.find(',');

            Tile tile;
            tile.x = stoull(line.substr(0, comma));
            tile.y = stoull(line.substr(comma + 1));
            tiles.emplace_back(tile);
        }

        int64_t largest = 0L;
        for (int i = 0; i < tiles.size() - 1; i++) {
            for (int j = i + 1; j < tiles.size(); j++) {
                int64_t area = (abs(tiles[i].x - tiles[j].x) + 1) * (abs(tiles[i].y - tiles[j].y) + 1);
                if (area > largest) {
                    largest = area;
                }
            }
        }
        std::cout << largest << std::endl;
        
        file.close();
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

