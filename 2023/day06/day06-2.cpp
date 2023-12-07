#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <limits>

struct Record {
    uint64_t time;
    uint64_t distance;
} record;

std::vector<std::string> input;

std::string concatenateGroup(std::string group) {
    std::string ret;
    
    group = group.substr(group.find(':') + 1);

    std::stringstream ss(group);
    std::string number;
    while (getline(ss, number, ' ')) {
        //  remove extraneous spaces
        number.erase(std::remove(number.begin(), number.end(), ' '), number.end());
        ret += number;
    }
    
    return ret;
}

void parseInput() {
    record.time = std::stoull(concatenateGroup(input.at(0)));
    record.distance = std::stoull(concatenateGroup(input.at(1)));
}

int findSolution() {
    uint64_t solutions = 0;
    for (uint64_t i = 0; i <= record.time; i++) {
        if ((record.time - i) * i > record.distance) {
            solutions++;
        }
    }
    
    return solutions;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2023/day06/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            input.push_back(line);
        }
        file.close();
        
        parseInput();
        std::cout << findSolution() << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}
