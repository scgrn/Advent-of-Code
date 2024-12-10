#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

std::vector<std::string> map;
int width, height;

std::unordered_map<std::string, int> trailheads;

struct Coord {
    int x;
    int y;
};

Coord dirs[] = {
    { 0, -1},
    { 1,  0},
    { 0,  1},
    {-1,  0}
};

std::string createHash(const Coord& coord) {
    std::stringstream ss;
    ss << coord.x << " " << coord.y;

    return ss.str();
}

void visit(Coord pos, int currentHeight, Coord trailhead) {
    if (currentHeight == 9) {
        trailheads[createHash(trailhead)]++;
        return;
    }

    for (int dir = 0; dir < 4; dir++) {
        Coord newPos{pos.x + dirs[dir].x, pos.y + dirs[dir].y};
        if (newPos.x >= 0 && newPos.x < width && newPos.y >= 0 && newPos.y < height) {
            if (map[newPos.y][newPos.x] - '0' == currentHeight + 1) {
                visit(newPos, currentHeight + 1, trailhead);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day10/input.txt");
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            map.push_back(line);
        }
        file.close();

        width = map.at(0).length();
        height = map.size();

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (map[y][x] == '0') {
                    trailheads[createHash(Coord{x, y})] = 0;
                    visit(Coord{x, y}, 0, Coord{x, y});
                }
            }
        }

        int total = 0;
        for (const auto& pair : trailheads) {
            total += pair.second;
        }
        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

