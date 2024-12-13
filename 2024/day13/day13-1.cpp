#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Vec2 {
    int x, y;
};

struct Machine {
    Vec2 a;
    Vec2 b;
    Vec2 prize;
};
std::vector<Machine> machines;

int solve(Machine machine) {
    int det = machine.a.x * machine.b.y - machine.a.y* machine.b.x;
    int a = (machine.prize.x * machine.b.y - machine.prize.y * machine.b.x) / det;
    int b = (machine.a.x * machine.prize.y - machine.a.y * machine.prize.x) / det;
    if (machine.a.x * a + machine.b.x * b == machine.prize.x &&
        machine.a.y * a + machine.b.y * b == machine.prize.y) {
        
        return a * 3 + b;
    } else {
        return 0;
    }
}
 
int main(int argc, char* argv[]) {
    std::ifstream file("2024/day13/input.txt");
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
        }
        file.close();

        Machine m;
        m.a = Vec2{94, 34};
        m.b = Vec2{22, 67};
        m.prize = Vec2{8400, 5400};
        std::cout << solve(m) << std::endl;

        m.a = Vec2{17, 86};
        m.b = Vec2{84, 37};
        m.prize = Vec2{7870, 6450};
        std::cout << solve(m) << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

