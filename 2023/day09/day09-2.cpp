#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <algorithm>

int64_t extrapolate(std::string line) {
    std::vector<int> readings;
    
    std::stringstream ss(line);
    std::string number;
    while (getline(ss, number, ' ')) {
        readings.push_back(atoi(number.c_str()));
    }
    std::reverse(readings.begin(), readings.end()); 

    std::vector<std::vector<int>> differences;
    std::vector<int> prev = readings;
    bool allZero = false;
    
    while (!allZero) {
        std::vector<int> diff;

        allZero = true;
        for (int i = 0; i < prev.size() - 1; i++) {
            int val = prev.at(i + 1) - prev.at(i);
            diff.push_back(val);
            if (val != 0) {
                allZero = false;
            }
        }
        
        differences.push_back(diff);
        prev = diff;
    }
    
    int prediction = 0;
    for (int i = 0; i < differences.size(); i++) {
        prediction += differences.at(i).at(differences.at(i).size() - 1);
    }
    prediction += readings.at(readings.size() - 1);
    
    return prediction;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2023/day09/input.txt");
    if (file.is_open()) {
        int64_t sum = 0;
        while (getline(file, line)) {
            sum += extrapolate(line);
        }
        file.close();
        
        std::cout << sum << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}

