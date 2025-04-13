#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

bool light[1000][1000];
struct Range {
    int x1, y1, x2, y2;
};

void set(Range range, bool on) {
    for (int y = range.y1; y <= range.y2; y++) {
        for (int x = range.x1; x <= range.x2; x++) {
            light[x][y] = on;
        }
    }
}

void toggle(Range range) {
    for (int y = range.y1; y <= range.y2; y++) {
        for (int x = range.x1; x <= range.x2; x++) {
            light[x][y] = !light[x][y];
        }
    }
}

Range parse(std::string line, int firstNumber) {
    Range range;

    std::stringstream ss(line);
    std::string str;
    int word = 0;

    while (getline(ss, str, ' ')) {
        if (word == firstNumber) {
            std::stringstream coordSS(str);
            std::string token;
            if (getline(coordSS, token, ',')) {
                range.x1 = stoi(token);
            }
            if (getline(coordSS, token, ',')) {
                range.y1 = stoi(token);
            }
        }
        if (word == firstNumber + 2) {
            std::stringstream coordSS(str);
            std::string token;
            if (getline(coordSS, token, ',')) {
                range.x2 = stoi(token);
            }
            if (getline(coordSS, token, ',')) {
                range.y2 = stoi(token);
            }
        }
        word++;
    }

    return range;
}

int main(int argc, char* argv[]) {
    std::ifstream file("2015/day06/input.txt");

    if (file.is_open()) {
        set(Range{0, 0, 999, 999}, false);

        std::string line;
        while (getline(file, line)) {
            if (line.rfind("turn on", 0) == 0) {
                Range range = parse(line, 2);
                set(range, true);
                continue;
            }
            if (line.rfind("turn off", 0) == 0) {
                Range range = parse(line, 2);
                set(range, false);
                continue;
            }
            if (line.rfind("toggle", 0) == 0) {
                Range range = parse(line, 1);
                toggle(range);
            }
        }
        file.close();

        int total = 0;
        for (int y = 0; y <= 999; y++) {
            for (int x = 0; x <= 999; x++) {
                if (light[x][y]) {
                    total++;
                }
            }
        }
        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

