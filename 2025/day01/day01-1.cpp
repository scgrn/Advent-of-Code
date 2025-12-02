#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2025/day01/input.txt");

    if (file.is_open()) {
        int pos = 50;
        int zeros = 0;
        
        while (getline(file, line)) {
            int dist = std::stoi(line.substr(1, std::string::npos));
            if (line[0] == 'R') {
                pos = (pos + dist) % 100;
            } else {
                pos -= dist;
                while (pos < 0) {
                    pos += 100;
                }
            }
            if (pos == 0) {
                zeros++;
            }
        }
        std::cout << zeros << std::endl;

        file.close();
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

