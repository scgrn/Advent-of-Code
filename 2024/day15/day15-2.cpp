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

void visualize() {
    for (int y = 0; y < height; y++) {
        std::cout << map[y] << std::endl;
    }
    std::cout << std::endl;
}

void expandMap() {
    for (int y = 0; y < height; y++) {
        std::string line = map[y];
        std::string newLine;
        
        for (char c : line) {
            if (c == '#') {
                newLine += "##";
            }
            if (c == 'O') {
                newLine += "[]";
            }
            if (c == '.') {
                newLine += "..";
            }
            if (c == '@') {
                newLine += "@.";
            }
        }
        
        map[y] = newLine;
    }
    width *= 2;
}

void findRobot() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y][x] == '@') {
                robot = Vec2{x, y};
                return;
            }
        }
    }
}

void moveHorizontal(int dir) {
    bool moveAllowed = true;

    Vec2 newPos = Vec2{robot.x + dirs[dir].x, robot.y + dirs[dir].y};
    if (map[newPos.y][newPos.x] == '#') {
        moveAllowed = false;
    }
    Vec2 pos = newPos;
    if (map[newPos.y][newPos.x] == '[' || map[newPos.y][newPos.x] == ']') {
        bool foundSpace = false;
        while (pos.x > 0 && pos.x < width - 1 && pos.y > 0 && pos.y < height - 1 && map[pos.y][pos.x] != '#') {
            pos.x += dirs[dir].x;
            pos.y += dirs[dir].y;
            if (map[pos.y][pos.x] == '.') {
                foundSpace = true;
                break;
            }
        }
        if (!foundSpace) {
            moveAllowed = false;
        }
    }

    if (moveAllowed) {
        //  shift tiles left
        if (dir == 2) {
            for (int x = pos.x; x < robot.x; x++) {
                map[pos.y][x] = map[pos.y][x + 1];
            }
        }

        //  shift tiles right
        if (dir == 3) {
            for (int x = pos.x; x > robot.x; x--) {
                map[pos.y][x] = map[pos.y][x - 1];
            }
        }
        map[robot.y][robot.x] = '.';
        robot.x += dirs[dir].x;
        robot.y += dirs[dir].y;
        map[robot.y][robot.x] = '@';
        
    }
}

bool canMoveBoxVertical(Vec2 box, int dir) {
    if (map[box.y][box.x] == ']') {
        box.x--;
    }

    int newRow = box.y + dirs[dir].y;

    char newLeft = map[newRow][box.x];
    char newRight = map[newRow][box.x + 1];

    if (newLeft == '#') {
        return false;
    }
    if (newRight == '#') {
        return false;
    }

    if (newLeft == '[' || newLeft == ']') {
        if (!canMoveBoxVertical(Vec2{box.x, newRow}, dir)) {
            return false;
        }
    }
    if (newRight == '[') {
        if (!canMoveBoxVertical(Vec2{box.x + 1, newRow}, dir)) {
            return false;
        }
    }

    return true;
}

void moveBoxVertical(Vec2 box, int dir) {
    if (map[box.y][box.x] == ']') {
        box.x--;
    }

    int newRow = box.y + dirs[dir].y;

    char newLeft = map[newRow][box.x];
    char newRight = map[newRow][box.x + 1];

    if (newLeft == '[' || newLeft == ']') {
        moveBoxVertical(Vec2{box.x, newRow}, dir);
    }
    if (newRight == '[') {
        moveBoxVertical(Vec2{box.x + 1, newRow}, dir);
    }

    map[box.y][box.x] = '.';
    map[box.y][box.x + 1] = '.';

    map[newRow][box.x] = '[';
    map[newRow][box.x + 1] = ']';
}

void moveVertical(int dir) {
    Vec2 newPos = Vec2{robot.x + dirs[dir].x, robot.y + dirs[dir].y};
    if (map[newPos.y][newPos.x] == '#') {
        return;
    }
    if (map[newPos.y][newPos.x] == '.') {
        map[robot.y][robot.x] = '.';
        robot = newPos;
        map[robot.y][robot.x] = '@';
        return;
    }
    if (canMoveBoxVertical(newPos, dir)) {
        moveBoxVertical(newPos, dir);
        map[robot.y][robot.x] = '.';
        robot = newPos;
        map[robot.y][robot.x] = '@';
    }
}

void simulate() {
    for (int move : instructions) {
        if (move == 2 || move == 3) {
            moveHorizontal(move);
        } else {
            moveVertical(move);
        }
    }
}

int sumGPS() {
    int sum = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y][x] == '[') {
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

        expandMap();
        findRobot();
        simulate();

        std::cout << sumGPS() << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

