#include <iostream>
#include <fstream>
#include <algorithm>

std::string digits[] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
};

int findFirstMatch(std::string line) {
    int firstIndex = 0;
    int firstLocation = 1000000;
    for (int i = 0; i < 20; i++) {
        int location = line.find(digits[i]);
        if (location != std::string::npos && location < firstLocation) {
            firstIndex = i;
            firstLocation = location;
        }
    }
    
    return firstIndex % 10;
}

int getCalibrationValue(std::string line) {
    int firstDigit = findFirstMatch(line);

    //  reverse input line and all digit strings
    std::reverse(line.begin(), line.end());
    for (int i = 0; i < 20; i++) {
        std::reverse(digits[i].begin(), digits[i].end());
    }
    int lastDigit = findFirstMatch(line);

    //  flip them all back for the next iteration
    for (int i = 0; i < 20; i++) {
        std::reverse(digits[i].begin(), digits[i].end());
    }
    
    std::string calibrationValue = std::to_string(firstDigit) + std::to_string(lastDigit);

    return atoi(calibrationValue.c_str());
}

int main(int argc, char* argv[]) {
    int sum = 0;

    std::string line;
    std::ifstream file("2023/day01/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            sum += getCalibrationValue(line);
        }
        file.close();
    }
    std::cout << sum << "\n";
    
    return 0;
}
