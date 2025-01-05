#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2018/day01/input.txt");

    if (file.is_open()) {
        int total = 0;
        while (getline(file, line)) {
            std::stringstream ss(line);
            total += atoi(line.c_str());
        }
        file.close();

        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

