#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

enum Dir {
    RIGHT = 0,
    UP,
    LEFT,
    DOWN
};

struct Beam {
    int x, y;
    Dir dir;
    bool dead;
};

std::vector<std::string> input;
int height, width;

std::vector<Beam> beams;

int simulate() {
    struct Tile {
        bool energized;
        bool passed[4];
    };
    Tile tiles[height][width];
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            tiles[y][x].energized = false;
            for (int i = 0; i < 4; i++) {
                tiles[y][x].passed[i] = false;
            }
        }
    }
    
    while (!beams.empty()) {
        for (int i = 0; i < beams.size(); i++) {
            tiles[beams[i].y][beams[i].x].energized = true;
            tiles[beams[i].y][beams[i].x].passed[beams[i].dir] = true;
            
            switch (beams[i].dir) {
                case RIGHT: {
                    if (input[beams[i].y][beams[i].x] == '\\') {
                        beams[i].dir = DOWN;
                        beams[i].y++;
                    } else if (input[beams[i].y][beams[i].x] == '/') {
                        beams[i].dir = UP;
                        beams[i].y--;
                    } else if (input[beams[i].y][beams[i].x] == '|') {
                        if (beams[i].y < height - 1) {
                            beams.push_back(Beam {beams[i].x, beams[i].y + 1, DOWN, false});
                        }
                        beams[i].dir = UP;
                        beams[i].y--;
                    } else {
                        beams[i].x++;
                    }
                    break;
                }
                case UP: {
                    if (input[beams[i].y][beams[i].x] == '\\') {
                        beams[i].dir = LEFT;
                        beams[i].x--;
                    } else if (input[beams[i].y][beams[i].x] == '/') {
                        beams[i].dir = RIGHT;
                        beams[i].x++;
                    } else if (input[beams[i].y][beams[i].x] == '-') {
                        if (beams[i].x > 0) {
                            beams.push_back(Beam {beams[i].x - 1, beams[i].y, LEFT, false});
                        }
                        beams[i].dir = RIGHT;
                        beams[i].x++;
                    } else {
                        beams[i].y--;
                    }
                    break;
                }
                case LEFT: {
                    if (input[beams[i].y][beams[i].x] == '\\') {
                        beams[i].dir = UP;
                        beams[i].y--;
                    } else if (input[beams[i].y][beams[i].x] == '/') {
                        beams[i].dir = DOWN;
                        beams[i].y++;
                    } else if (input[beams[i].y][beams[i].x] == '|') {
                        if (beams[i].y < height - 1) {
                            beams.push_back(Beam {beams[i].x, beams[i].y + 1, DOWN, false});
                        }
                        beams[i].dir = UP;
                        beams[i].y--;
                    } else {
                        beams[i].x--;
                    }
                    break;
                }
                case DOWN: {
                    if (input[beams[i].y][beams[i].x] == '\\') {
                        beams[i].dir = RIGHT;
                        beams[i].x++;
                    } else if (input[beams[i].y][beams[i].x] == '/') {
                        beams[i].dir = LEFT;
                        beams[i].x--;
                    } else if (input[beams[i].y][beams[i].x] == '-') {
                        if (beams[i].x > 0) {
                            beams.push_back(Beam {beams[i].x - 1, beams[i].y, LEFT, false});
                        }
                        beams[i].dir = RIGHT;
                        beams[i].x++;
                    } else {
                        beams[i].y++;
                    }
                    break;
                }
                default: break;
            }
            
            if (beams[i].x < 0 || beams[i].x >= width || beams[i].y < 0 || beams[i].y >= height) {
                beams[i].dead = true;
            } else {
                if (tiles[beams[i].y][beams[i].x].passed[beams[i].dir]) {
                    beams[i].dead = true;
                }
            }
        }

        for (int i = beams.size() - 1; i >= 0; i--) {
            if (beams[i].dead) {
                beams.erase(beams.begin() + i);
            }
        }
    }
    
    int sum = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (tiles[y][x].energized) {
                sum++;
            }
        }
    }
    
    return sum;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2023/day16/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            input.push_back(line);
        }
        file.close();

        width = input[0].length();
        height = input.size();

        int max = 0;

        for (int y = 0; y < height; y++) {
            beams.push_back(Beam {0, y, RIGHT, false});
            max = std::max(max, simulate());

            beams.push_back(Beam {width - 1, y, LEFT, false});
            max = std::max(max, simulate());
        }
        
        for (int x = 0; x < width; x++) {
            beams.push_back(Beam {x, 0, DOWN, false});
            max = std::max(max, simulate());

            beams.push_back(Beam {x, height - 1, UP, false});
            max = std::max(max, simulate());
        }

        std::cout << max << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}
