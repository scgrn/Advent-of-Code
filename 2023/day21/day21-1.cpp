#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

struct Position {
    int x, y;
};
Position start;

std::vector<std::string> input;
int height, width;

std::vector<Position> positions;
std::unordered_map<std::string, bool> cache;

void findStart() {
    for (start.y = 0; start.y < height; start.y++) {
        for (start.x = 0; start.x < width; start.x++) {
            if (input[start.y][start.x] == 'S') {
                input[start.y][start.x] = '.';
                return;
            }
        }
    }
}

std::string createHash(Position position) {
    std::stringstream ss;
    ss << position.x << " " << position.y;
    return ss.str();    
}

bool valid(Position position) {
    if (position.x >= 0 && position.x < width && position.y >= 0 && position.y < height) {
        std::string hash = createHash(position);
        if (cache.find(hash) == cache.end()) {
            cache.emplace(hash, true);
            return (input[position.y][position.x] == '.');
        }
    }
    return false;
}

std::vector<Position> step() {
    cache.clear();
    std::vector<Position> newPositions;
    
    for (auto& position : positions) {
        if (valid({position.x, position.y - 1})) {
            newPositions.push_back({position.x, position.y - 1});
        }
        if (valid({position.x, position.y + 1})) {
            newPositions.push_back({position.x, position.y + 1});
        }
        if (valid({position.x + 1, position.y})) {
            newPositions.push_back({position.x + 1, position.y});
        }
        if (valid({position.x - 1, position.y})) {
            newPositions.push_back({position.x - 1, position.y});
        }
    }
    
    return newPositions;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2023/day21/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            input.push_back(line);
        }
        file.close();

        width = input[0].length();
        height = input.size();
        
        findStart();
        
        positions.push_back(start);
        for (int i = 0; i < 64; i++ ) {        
            positions = step();
        }

        std::cout << positions.size() << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}
