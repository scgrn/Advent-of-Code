#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<long> results;

void evaluate(std::vector<int> &numbers, int index, long currentResult) {
    if (index == numbers.size()) {
        results.emplace_back(currentResult);
    } else {
        evaluate(numbers, index + 1, currentResult + numbers[index]);
        evaluate(numbers, index + 1, currentResult * numbers[index]);
    }
}

long process(std::string line) {
    results.clear();

    long testValue;
    std::vector<int> numbers;

    int colonPos = line.find(':');
    testValue = atol(line.substr(0, colonPos).c_str());

    std::stringstream ss(line.substr(colonPos + 2, line.length() - (colonPos + 2)));
    std::string numberStr;
    while (getline(ss, numberStr, ' ')) {
        int number = atoi(numberStr.c_str());
        numbers.emplace_back(number);
    }

    evaluate(numbers, 1, numbers[0]);

    for (long result : results) {
        if (result == testValue) {
            return testValue;
        }
    }

    return 0;
}

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day07/input.txt");
    std::string line;

    if (file.is_open()) {
        long total = 0;
        while (getline(file, line)) {
            total += process(line);
        }
        file.close();
        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

