#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

int x = 0;
int y = 0;

std::unordered_map<std::string, int> houses;

std::string createHash() {
    std::stringstream ss;
    ss << x << " " << y;
    return ss.str();
}

void visit() {
    std::string hash = createHash();
    if (houses.find(hash) == houses.end()) {
        houses.emplace(hash, 1);
    } else {
        houses[hash]++;
    }
}

int main(int argc, char* argv[]) {
    std::ifstream file("2015/day03/input.txt");

    visit();

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            for (char c : line) {
                switch (c) {
                    case '^': y--; visit(); break;
                    case 'v': y++; visit(); break;
                    case '<': x--; visit(); break;
                    case '>': x++; visit(); break;
                    default: break;
                };
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

