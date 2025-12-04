#include <iostream>
#include <fstream>

int findLargest(std::string const& line) {
    char largestDigit = line[0];
    int largestDigitPosition = 0;
    int ret;
    
    for (int i = 1; i < line.length() - 1; i++) {
        if (line[i] > largestDigit) {
            largestDigit = line[i];
            largestDigitPosition = i;
        }
    }
    ret = (largestDigit - '0') * 10;
    
    largestDigitPosition++;
    largestDigit = line[largestDigitPosition];
    for (int i = largestDigitPosition; i < line.length(); i++) {
        if (line[i] > largestDigit) {
            largestDigit = line[i];
            largestDigitPosition = i;
        }
    }
    ret += (largestDigit - '0');
    
    return ret;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2025/day03/input.txt");

    if (file.is_open()) {
        int total = 0;
        while (getline(file, line)) {
            total += findLargest(line);
        }
        std::cout << total << std::endl;
        file.close();
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

