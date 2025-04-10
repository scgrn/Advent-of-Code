#include <iostream>
#include <fstream>

bool isNice(std::string line) {
    bool pairFound = false;
    for (int i = 0; i < line.length() - 3; i++) {
        for (int j = i + 2; j < line.length() - 1; j++) {
            if (line[i] == line[j] && line[i + 1] == line[j + 1]) {
                pairFound = true;
                break;
            }
        }
    }
    if (!pairFound) {
        return false;
    }

    for (int i = 0; i < line.length() - 2; i++) {
        if (line[i] == line[i + 2]) {
            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    std::ifstream file("2015/day05/input.txt");

    if (file.is_open()) {
        int total = 0;
        std::string line;

        while (getline(file, line)) {
            if (isNice(line)) {
                total++;
            }
        }

        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

