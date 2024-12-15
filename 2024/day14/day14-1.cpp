#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

const int WIDTH = 101;
const int HEIGHT = 103;
const int SECONDS = 100;

struct Vec2 {
    int x, y;
};

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day14/input.txt");
    std::string line;
    std::vector<int> soup;
    std::vector<Vec2> robots;

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

            Vec2 robot;
            robot.x = (pos.x + (vel.x * SECONDS)) % WIDTH;
            robot.y = (pos.y + (vel.y * SECONDS)) % HEIGHT;
            while (robot.x < 0) {
                robot.x += WIDTH;
            }
            while (robot.y < 0) {
                robot.y += HEIGHT;
            }
            robots.emplace_back(robot);
        }

        Vec2 center = Vec2{(WIDTH - 1) / 2, (HEIGHT - 1) / 2};

        int quadrants[4] = {0, 0, 0, 0};
        for (auto& robot: robots) {
            if (robot.x < center.x) {
                if (robot.y < center.y) {
                    quadrants[0]++;
                }
                if (robot.y > center.y) {
                    quadrants[1]++;
                }
            }
            if (robot.x > center.x) {
                if (robot.y < center.y) {
                    quadrants[2]++;
                }
                if (robot.y > center.y) {
                    quadrants[3]++;
                }
            }
        }

        int total = 1;
        for (int i = 0; i < 4; i++) {
            if (quadrants[i] != 0) {
                total *= quadrants[i];
            }
        }
        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

