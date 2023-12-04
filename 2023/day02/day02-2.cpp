#include <iostream>
#include <fstream>
#include <sstream>

int powerOfMinimumSet(std::string line) {
    line = line.substr(line.find(':') + 1);

    int minRed = 0;
    int minGreen = 0;
    int minBlue = 0;
    
    std::stringstream ss(line);
    std::string turn;
    while (getline(ss, turn, ';')) {
        std::stringstream tss(turn);
        std::string color;
        while (getline(tss, color, ',')) {
            color = color.substr(turn.find(' ') + 1);

            int quantity = atoi(color.substr(0, color.find(" ")).c_str());
            if (color.find("red") != std::string::npos) {
                minRed = std::max(minRed, quantity);
            }
            if (color.find("green") != std::string::npos) {
                minGreen = std::max(minGreen, quantity);
            }
            if (color.find("blue") != std::string::npos) {
                minBlue = std::max(minBlue, quantity);
            }
        }
    };

    return minRed * minGreen * minBlue;
}

int main(int argc, char* argv[]) {
    int sum = 0;
    
    std::string line;
    std::ifstream file("2023/day02/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            sum += powerOfMinimumSet(line);
        }
        file.close();
    }
    std::cout << sum << "\n";
    
    return 0;
}

