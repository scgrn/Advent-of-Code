#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

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
    int det = machine.a.x * machine.b.y - machine.a.y * machine.b.x;
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
        std::regex pattern(R"([0-9]+)");
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

        int total = 0;
        for (int i = 0; i < soup.size() / 6; i++) {
            Machine machine;
            machine.a = Vec2{soup[i * 6 + 0], soup[i * 6 + 1]};
            machine.b = Vec2{soup[i * 6 + 2], soup[i * 6 + 3]};
            machine.prize = Vec2{soup[i * 6 + 4], soup[i * 6 + 5]};
            total += solve(machine);
        }
        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

