//  requires Mustard Engine
//  https://github.com/scgrn/Mustard-Engine

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

#include "mustard.h"

const int WIDTH = 101;
const int HEIGHT = 103;

const float TARGET = 7623.0f;

bool grid[WIDTH][HEIGHT];

struct Robot {
    AB::Vec2 startPos, pos, vel;
};
std::vector<Robot> robots;
bool updating;

AB::Font font;
float seconds;

int timer;

class App : public AB::Application {
    public:
        void startup() {
            font.load("default1");

            std::ifstream file("../input.txt");
            std::string line;
            std::vector<int> soup;

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

                for (AB::u32 i = 0; i < soup.size() / 4; i++) {
                    Robot robot;
                    robot.startPos = AB::Vec2(soup[i * 4 + 0], soup[i * 4 + 1]);
                    robot.pos = robot.startPos;
                    robot.vel = AB::Vec2(soup[i * 4 + 2], soup[i * 4 + 3]);
                    robots.emplace_back(robot);
                }
            } else {
                std::cout << "Couldn't read input!" << std::endl;
            }
            
            updating = true;
            seconds = TARGET - 3.0f;
            timer = 0;
        };

        void shutdown() {
        };

        void updateRobots() {
            for (Robot& robot : robots) {
                robot.pos = robot.startPos + (robot.vel * seconds);

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

        void update() {
            if (AB::input.wasKeyPressed(AB::Input::Scancodes::ESCAPE)) {
                AB::quit();
            }
            if (AB::input.wasKeyPressed(AB::Input::Scancodes::SPACE)) {
                updating = !updating;
            }
            if (AB::input.wasKeyPressed(AB::Input::Scancodes::LEFT)) {
                seconds = (int)seconds - (AB::input.isKeyPressed(AB::Input::Scancodes::LSHIFT) ? 15 : 1);
                updateRobots();
                if (seconds < TARGET) {
                    timer = 0;
                }
            }
            if (AB::input.wasKeyPressed(AB::Input::Scancodes::RIGHT)) {
                seconds = (int)seconds + (AB::input.isKeyPressed(AB::Input::Scancodes::LSHIFT) ? 15 : 1);
                updateRobots();
            }

            if (updating) {
                if (seconds < TARGET || timer > 60) {
                    seconds += 1.0f / 120.0f;
                    if (timer == 0 && seconds >= TARGET) {
                        seconds = TARGET;
                    }
                } else {
                    timer++;
                }
                updateRobots();
            }
        }

        void render() {
            AB::RenderLayer::textureCache.invalidate();

            AB::RenderLayer::Quad quad;
            quad.pos = AB::Vec2(WIDTH / 2, HEIGHT / 2) * 6.0f;
            quad.size = AB::Vec2(WIDTH + 2, HEIGHT + 2);
            quad.scale = AB::Vec2(6, 6);
            quad.rotation = 0.0f;
            quad.uv = AB::Vec4(0, 0, 0, 0);
            quad.textureID = 0;
            quad.color = AB::Vec4(0.0, 0.0, 0.01, 0.2);
            AB::renderer.layers[0]->renderQuad(quad);
            AB::renderer.render(AB::camera2d);
            
            for (Robot robot : robots) {
                AB::RenderLayer::Quad quad;
                quad.pos = robot.pos * 6.0f;
                quad.size = AB::Vec2(1, 1);
                quad.scale = AB::Vec2(6, 6);
                quad.rotation = 0.0f;
                quad.uv = AB::Vec4(0, 0, 0, 0);
                quad.textureID = 0;
                if (seconds == 7623.0f) {
                    quad.color = AB::Vec4(0.0, 0.267, 0.224, 1.0f);
                } else {
                    quad.color = AB::Vec4(0.5, 0.5, 0.5, 0.5);
                }

                AB::renderer.layers[0]->renderQuad(quad);
            }
            AB::renderer.render(AB::camera2d);

            font.printString(AB::renderer.layers[0], 10, 20, 1, AB::Font::LEFT, std::to_string(seconds));
            AB::renderer.render(AB::camera2d);
        }
};

AB::Application* AB::createApplication() {
    return new App();
}

