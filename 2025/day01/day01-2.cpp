#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2025/day01/input.txt");

    if (file.is_open()) {
        int pos = 50;
        int zeros = 0;
        
        while (getline(file, line)) {
            int dist = std::stoi(line.substr(1));
            zeros += dist / 100;
            dist %= 100;

            if (line[0] == 'L') {
                dist = -dist;
            }
            int next = pos + dist;

            if (next > 99) {
                next -= 100;
                zeros++;
            } else if (next == 0) {
                zeros++;
            } else if (next < 0 && pos != 0) {
                next += 100;
                zeros++;
            }

            pos = (next + 100) % 100;
        }
        std::cout << zeros << std::endl;

        file.close();
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

