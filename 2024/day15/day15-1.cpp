#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Vec2 {
    int x, y;
};

Vec2 dirs[] = {
    { 0, -1},
    { 0,  1},
    {-1,  0},
    { 1,  0}
};

std::vector<std::string> map;
int width, height;

Vec2 robot;
std::vector<int> instructions;

void findRobot() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y][x] == '@') {
                robot = Vec2{x, y};
                map[y][x] = '.';
                return;
            }
        }
    }
}

void simulate() {
    for (int move : instructions) {
        bool moveAllowed = true;

        Vec2 newPos = Vec2{robot.x + dirs[move].x, robot.y + dirs[move].y};
        if (map[newPos.y][newPos.x] == '#') {
            moveAllowed = false;
        }
        if (map[newPos.y][newPos.x] == 'O') {
            bool foundSpace = false;
            Vec2 pos = newPos;
            while (pos.x > 0 && pos.x < width - 1 && pos.y > 0 && pos.y < height - 1&& map[pos.y][pos.x] != '#') {
                pos.x = pos.x + dirs[move].x;
                pos.y = pos.y + dirs[move].y;
                if (map[pos.y][pos.x] == '.') {
                    foundSpace = true;
                    map[pos.y][pos.x] = 'O';
                    break;
                }
            }
            if (!foundSpace) {
                moveAllowed = false;
            }
        }

        if (moveAllowed) {
            map[robot.y][robot.x] = '.';
            robot.x += dirs[move].x;
            robot.y += dirs[move].y;
        }
    }
}

int sumGPS() {
    int sum = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y][x] == 'O') {
                sum += y * 100 + x;
            }
        }
    }

    return sum;
}

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day15/input.txt");
    std::string line;

    if (file.is_open()) {
        bool loadedMap = false;
        while (getline(file, line)) {
            if (!loadedMap) {
                //  read map
                if (line.empty()) {
                    width = map[0].length();
                    height = map.size();
                    loadedMap = true;
                } else {
                    map.emplace_back(line);
                }
            } else {
                //  read robot instructions
                const std::string dirString = "^v<>";
                for (char c : line) {
                    int dir = dirString.find(c);
                    if (dir != std::string::npos) {
                        instructions.emplace_back(dir);
                    }
                }
            }
        }
        file.close();

        findRobot();
        simulate();

        std::cout << sumGPS() << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

