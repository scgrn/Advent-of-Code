#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

struct Vec2 {
    int x, y;
};
Vec2 santas[2];

std::unordered_map<std::string, int> houses;

std::string createHash(Vec2 const& v) {
    std::stringstream ss;
    ss << v.x << " " << v.y;
    return ss.str();
}

void visit(Vec2 const& v) {
    std::string hash = createHash(v);
    if (houses.find(hash) == houses.end()) {
        houses.emplace(hash, 1);
    } else {
        houses[hash]++;
    }
}

int main(int argc, char* argv[]) {
    std::ifstream file("2015/day03/input.txt");

    for (int i = 0; i < 2; i++) {
        santas[i].x = 0;
        santas[i].y = 0;
        visit(santas[i]);
    }

    if (file.is_open()) {
        std::string line;
        int instruction = 0;
        while (getline(file, line)) {
            for (char c : line) {
                int index = instruction % 2;
                switch (c) {
                    case '^': santas[index].y--; visit(santas[index]); break;
                    case 'v': santas[index].y++; visit(santas[index]); break;
                    case '<': santas[index].x--; visit(santas[index]); break;
                    case '>': santas[index].x++; visit(santas[index]); break;
                    default: break;
                };
                instruction++;
            }
        }
        file.close();

        int total = 0;
        for (auto& house : houses) {
            total++;
        }
        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

