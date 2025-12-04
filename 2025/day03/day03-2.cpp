#include <iostream>
#include <fstream>
#include <cstdint>

uint64_t findLargest(std::string const& line) {
    int largestDigitPosition = -1;
    uint64_t ret = 0;

    for (int i = 0; i < 12; i++) {
        largestDigitPosition++;
        char largestDigit = line[largestDigitPosition];
        for (int j = largestDigitPosition + 1; j < line.length() - (11 - i); j++) {
            if (line[j] > largestDigit) {
                largestDigit = line[j];
                largestDigitPosition = j;
            }
        }
        ret = 10 * ret + (largestDigit - '0');
    }

    return ret;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2025/day03/input.txt");

    if (file.is_open()) {
        uint64_t total = 0;
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

