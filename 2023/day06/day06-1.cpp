#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <limits>

struct Record {
    int time;
    int distance;
};

std::vector<std::string> input;
std::vector<Record> records;

std::vector<int> splitGroup(std::string group) {
    std::vector<int> ret;

    group = group.substr(group.find(':') + 1);

    std::stringstream ss(group);
    std::string number;
    while (getline(ss, number, ' ')) {
        //  remove extraneous spaces
        number.erase(std::remove(number.begin(), number.end(), ' '), number.end());
        
        if (number.size() > 0) {
            ret.push_back(atoi(number.c_str()));
        }
    }
    
    return ret;
}

void parseInput() {
    std::vector<int> times = splitGroup(input.at(0));
    std::vector<int> distances = splitGroup(input.at(1));
    
    for (int i = 0; i < times.size(); i++) {
        Record record;
        record.time = times.at(i);
        record.distance = distances.at(i);
        records.push_back(record);
    }
}

int findSolution() {
    int ret = 1;
    
    for (Record record : records) {
        int solutions = 0;
        for (int i = 0; i <= record.time; i++) {
            if ((record.time - i) * i > record.distance) {
                solutions++;
            }
        }
        ret *= solutions;
    }
    
    return ret;
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
