#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> map;
int width, height;

struct{
    int dx, dy;
} dirs[] = {
    { 0, -1},
    { 1,  0},
    { 0,  1},
    {-1,  0}
};

struct Step {
    struct {int x; int y;} pos;
    int dir;
};
std::vector<Step> initialPath;
std::vector<Step> visited;

Step findGuard() {
    Step ret;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map.at(y)[x] == '^') {
                return Step{{x, y}, 0};
            }
        }
    }

    return ret;
}

bool wasVisited(Step step, std::vector<Step> &path, bool checkDir = true) {
    if (checkDir) {
        for (Step prev : path) {
            if (step.pos.x == prev.pos.x && step.pos.y == prev.pos.y && step.dir == prev.dir) {
                return true;
            }
        }
    } else {
        for (Step prev : path) {
            if (step.pos.x == prev.pos.x && step.pos.y == prev.pos.y) {
                return true;
            }
        }
    }

    return false;
}

bool simulatePatrol(Step guard, bool populateInitialPath) {
    visited.clear();
    for (;;) {
        int nx = guard.pos.x + dirs[guard.dir].dx;
        int ny = guard.pos.y + dirs[guard.dir].dy;

        if (nx < 0 || nx >= width || ny < 0 || ny >= height) {
            return false;
        }
        
        if (map.at(ny)[nx] == '#') {
            guard.dir = (guard.dir + 1) % 4;
        } else {
            guard.pos.x = nx;
            guard.pos.y = ny;

            if (populateInitialPath) {
                if (!wasVisited(guard, initialPath, false)) {
                    initialPath.emplace_back(guard);
                }
            }
        }

        if (!populateInitialPath) {
            if (wasVisited(guard, visited, true)) {
                return true;  //  in a loop!
            }
            visited.emplace_back(guard);
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

        simulatePatrol(findGuard(), true);

        int total = 0;
        for (int i = 0; i < initialPath.size() - 1; i++) {
            Step guard = initialPath[i];
            Step obstruction = initialPath[i + 1];
            
            map.at(obstruction.pos.y)[obstruction.pos.x] = '#';
            if (simulatePatrol(guard, false)) {
                total++;
            }
            map.at(obstruction.pos.y)[obstruction.pos.x] = '.';
        }
        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

