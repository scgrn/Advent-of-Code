#include <iostream>
#include <fstream>
#include <sstream>

struct Vec2 {
    int x, y;
};

Vec2 dirs[] = {
    { 0, -1},
    {-1,  0},
    { 0,  1},
    { 1,  0}
};

Vec2 pos;
unsigned int dir;

int main(int argc, char* argv[]) {
    std::ifstream file("2016/day01/input.txt");

    if (file.is_open()) {
        pos = Vec2{0, 0};
        dir = 0;

        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string str;
            while (getline(ss, str, ',')) {
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

                pos.x += dirs[dir].x * dist;
                pos.y += dirs[dir].y * dist;
            }
        }
        file.close();

        std::cout << std::abs(pos.x) + std::abs(pos.y) << std::endl;
   } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

