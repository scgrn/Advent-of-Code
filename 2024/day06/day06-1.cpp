#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> map;
int width, height;

struct Dir {
    int dx, dy;
};

Dir dirs[] = {
    { 0, -1},
    { 1,  0},
    { 0,  1},
    {-1,  0}
};

struct Guard {
    int x, y;
    int dir;
} guard;

void findGuard() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map.at(y)[x] == '^') {
                guard.x = x;
                guard.y = y;
                guard.dir = 0;

                return;
            }
        }
    }
}

int simulatePatrol() {
    int positions = 1;

    map.at(guard.y)[guard.x] = 'X';
    for (;;) {
        int nx = guard.x + dirs[guard.dir].dx;
        int ny = guard.y + dirs[guard.dir].dy;

        if (nx < 0 || nx >= width || ny < 0 || ny >= height) {
            return positions;
        }
        
        if (map.at(ny)[nx] == '#') {
            guard.dir = (guard.dir + 1) % 4;
        } else {
            if (map.at(ny)[nx] != 'X') {
                positions++;
                map.at(ny)[nx] = 'X';
            }
            guard.x = nx;
            guard.y = ny;
        }
    }
}

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day06/input.txt");
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            map.push_back(line);
        }
        file.close();
        
        width = map.at(0).length();
        height = map.size();

        findGuard();
        std::cout << simulatePatrol() << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

