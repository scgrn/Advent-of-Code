#include <iostream>
#include <fstream>
#include <sstream>

bool turnIsValid(std::string turn) {
    std::stringstream ss(turn);
    std::string color;
    while (getline(ss, color, ',')) {
        color = color.substr(turn.find(' ') + 1);

        int quantity = atoi(color.substr(0, color.find(" ")).c_str());
        if (color.find("red") != std::string::npos) {
            if (quantity > 12) {
                return false;
            }
        }
        if (color.find("green") != std::string::npos) {
            if (quantity > 13) {
                return false;
            }
        }
        if (color.find("blue") != std::string::npos) {
            if (quantity > 14) {
                return false;
            }
        }
    }
    return true;
}

bool gameIsValid(std::string line) {
    line = line.substr(line.find(':') + 1);

    std::stringstream ss(line);
    std::string turn;
    while (getline(ss, turn, ';')) {
        if (!turnIsValid(turn)) {
            return false;
        }
    };

    return true;
}

int main(int argc, char* argv[]) {
    int sum = 0;
    int game = 1;
    
    std::string line;
    std::ifstream file("2023/day02/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            if (gameIsValid(line)) {
                sum += game;
            }
            game++;
        }
        file.close();
    }
    std::cout << sum << "\n";
    
    return 0;
}

