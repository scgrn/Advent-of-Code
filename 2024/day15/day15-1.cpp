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
    std::cout << "ROBOT NOT FOUND" << std::endl;
}

void simulate() {
    for (int move : instructions) {
        Vec2 pos = robot;
        bool moveAllowed = true;

        newRobot = Vec2{robot.x + dirs[move].x, robot.y + dirs[move].y};
        if (map[pos.y][pos.x] == '#') {
            moveAllowed = false;
        }
        if (map[pos.y][pos.x] == 'O') {
            // scan to edge and make sure there is at least one empty space
            
        }
/*
        while (pos.x > 0 && pos.x < width - 1 && pos.y > 0 && pos.y < height - 1) {
            pos.x = pos.x + dirs[move].x;
            pos.y = pos.y + dirs[move].y;
            if (map[pos.y][pos.x] == '#') {
                break;
            }
            if (map[pos.y][pos.x] == 'O') {
                robot = pos;
                map[robot.y][robot.x] = '.';
                continue;
            }
        }
*/
        if (moveAllowed) {
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
    std::ifstream file("2024/day15/testInput.txt");
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
                    } else {
                        std::cout << "UNKNOWN CHARACTER" << std::endl;
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

