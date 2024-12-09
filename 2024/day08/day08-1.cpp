#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

struct Coord {
    int x;
    int y;
};

std::unordered_map<char, std::vector<Coord>> antennas;
std::unordered_map<std::string, bool> antinodes;

int width, height;

std::string createHash(const Coord& coord) {
    std::stringstream ss;
    ss << coord.x << " " << coord.y;

    return ss.str();
}

void calculateAntinodes() {
    for (auto antenna : antennas) {
        std::vector<Coord> &antennaList = antenna.second;
        for (int i = 0; i < antennaList.size(); i++) {
            for (int j = 0; j < antennaList.size(); j++) {
                if (i != j) {
                    Coord antinode;
                    antinode.x = antennaList[j].x + (antennaList[j].x - antennaList[i].x);
                    antinode.y = antennaList[j].y + (antennaList[j].y - antennaList[i].y);

                    if (antinode.x >= 0 && antinode.x < width && antinode.y >= 0 && antinode.y < height) {
                        antinodes[createHash(antinode)] = true;
                    }
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day08/input.txt");
    std::string line;
    
    if (file.is_open()) {
        int y = 0;
        while (getline(file, line)) {
            width = line.length();
            for (int x = 0; x < line.length(); x++) {
                char c = line[x];
                if (c != '.') {
                    antennas[c].emplace_back(Coord{x, y});
                }
            }
            y++;
        }
        height = y;
        file.close();

        calculateAntinodes();

        std::cout << antinodes.size() << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

