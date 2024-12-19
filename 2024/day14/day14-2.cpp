#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <cmath>

const int WIDTH = 101;
const int HEIGHT = 103;

struct Vec2 {
    int x, y;
};

struct Robot {
    Vec2 startPos, pos, vel;
};
std::vector<Robot> robots;

int calculateScore() {
    bool grid[WIDTH][HEIGHT];

    memset(grid, 0, sizeof(grid));
    for (Robot& robot : robots) {
        grid[(int)robot.pos.x][(int)robot.pos.y] = true;
    }
    
    int sum = 0;
    for (int y = 0; y < HEIGHT; y++) {
        int span = 0;
        int largestSpan = 0;
        for (int x = 0; x < WIDTH; x++) {
            if (grid[x][y]) {
                span++;
                if (span > largestSpan) {
                    largestSpan = span;
                }
            } else {
                span = 0;
            }
        }
        sum += largestSpan;
    }
    
    return sum;
}

void simulate(int seconds) {
    for (Robot& robot : robots) {
        robot.pos.x = robot.startPos.x + (robot.vel.x * seconds);
        robot.pos.y = robot.startPos.y + (robot.vel.y * seconds);

        while (robot.pos.x < 0) {
            robot.pos.x += WIDTH;
        }
        while (robot.pos.x >= WIDTH) {
            robot.pos.x -= WIDTH;
        }
        while (robot.pos.y < 0) {
            robot.pos.y += HEIGHT;
        }
        while (robot.pos.y >= HEIGHT) {
            robot.pos.y -= HEIGHT;
        }
    }
}

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day14/input.txt");
    std::string line;

    if (file.is_open()) {
        std::regex pattern(R"(-?[0-9]+)");
        std::smatch matches;
        std::vector<int> soup;

        while (getline(file, line)) {
            auto begin = std::sregex_iterator(line.begin(), line.end(), pattern);
            auto end = std::sregex_iterator();
            
            for (std::sregex_iterator i = begin; i != end; i++) {
                std::smatch match = *i;
                std::string matchStr = match.str();
                soup.emplace_back(atoi(matchStr.c_str()));
            }
        }
        file.close();

        for (int i = 0; i < soup.size() / 4; i++) {
            Vec2 pos = Vec2{soup[i * 4 + 0], soup[i * 4 + 1]};
            Vec2 vel = Vec2{soup[i * 4 + 2], soup[i * 4 + 3]};

            Robot robot;
            robot.startPos = Vec2{soup[i * 4 + 0], soup[i * 4 + 1]};
            robot.pos.x = robot.startPos.x;
            robot.pos.y = robot.startPos.y;
            robot.vel = Vec2{soup[i * 4 + 2], soup[i * 4 + 3]};
            robots.emplace_back(robot);
        }

        int largest = 0;
        int largestScore = 0;
        for (int seconds = 0; seconds < WIDTH * HEIGHT; seconds++) {
            simulate(seconds);
            int score = calculateScore();
            if (score > largestScore) {
                largestScore = score;
                largest = seconds;
            }
        }
        std::cout << largest << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

