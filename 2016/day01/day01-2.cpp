#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

struct Vec2 {
    int x, y;
};

Vec2 dirs[] = {
    { 0, -1},
    {-1,  0},
    { 0,  1},
    { 1,  0}
};

std::unordered_map<std::string, bool> map;

Vec2 pos;
unsigned int dir;

std::string createHash() {
    std::stringstream ss;
    ss << pos.x << " " << pos.y;
    return ss.str();
}

int main(int argc, char* argv[]) {
    std::ifstream file("2016/day01/input.txt");

    map.emplace(createHash(), true);

    if (file.is_open()) {
        pos = Vec2{0, 0};
        dir = 0;

        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string str;
            bool done = false;
            while (getline(ss, str, ',') && !done) {
                if (std::isspace(str[0])) {
                    str = str.substr(1);
                }
                if (str[0] == 'L') {
                    dir = (dir + 1) % 4;
                } else {
                    dir = (dir - 1) % 4;
                }
                str = str.substr(1);
                int dist = atoi(str.c_str());

                for (int i = 0; i < dist; i++) {
                    pos.x += dirs[dir].x;
                    pos.y += dirs[dir].y;

                    std::string hash = createHash();
                    if (map.find(hash) == map.end()) {
                        map.emplace(hash, true);
                    } else {
                        done = true;
                        break;
                    }
                }
            }
        }
        file.close();

        std::cout << std::abs(pos.x) + std::abs(pos.y) << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

