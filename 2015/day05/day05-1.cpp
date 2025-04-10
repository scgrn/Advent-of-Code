#include <iostream>
#include <fstream>

bool isNice(std::string line) {
    const std::string VOWELS = "aeiou";
    const std::string prohibited[4] = {"ab", "cd", "pq", "xy"};

    int vowelsUsed = 0;
    for (char v : VOWELS) {
        for (char c : line) {
            if (c == v) {
                vowelsUsed++;
            }
        }
    }
    if (vowelsUsed < 3) {
        return false;
    }

    bool doubleLetters = false;
    for (int i = 0; i < line.length() - 1; i++) {
        if (line[i] == line[i + 1]) {
            doubleLetters = true;
            break;
        }
    }
    if (!doubleLetters) {
        return false;
    }

    for (int i = 0; i < 4; i++) {
        if (line.find(prohibited[i]) != std::string::npos) {
            return false;
        }
    }

    return true;
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

