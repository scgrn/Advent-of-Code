#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <numeric>

struct Location {
    std::string left, right;
};

std::vector<std::string> input;
std::string directions;
std::unordered_map<std::string, Location> map;
std::vector<std::string> startingNodes;

void parseInput() {
    directions = input.at(0);

    for (int i = 2; i < input.size(); i++) {
        std::string line = input.at(i);
        
        Location location;
        location.left = line.substr(7, 3);
        location.right = line.substr(12, 3);
        
        std::string start = line.substr(0, 3);
        map.emplace(start, location);
        
        if (start[2] == 'A') {
            startingNodes.push_back(start);
        }
    }
}

uint64_t traverse(std::string start) {
    std::string currentLocation = start;
    uint64_t steps = 0;
    
    while (currentLocation[2] != 'Z') {
        if (directions[steps % directions.length()] == 'L') {
            currentLocation = map.at(currentLocation).left;
        } else {
            currentLocation = map.at(currentLocation).right;
        }
        steps++;
    }
    
    return steps;
}

uint64_t findAllPaths() {
    uint64_t lcm = 1;
    for (auto startingNode : startingNodes) {
        uint64_t period = traverse(startingNode);
        lcm = std::lcm(period, lcm);
    }
    
    return lcm;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2023/day08/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            input.push_back(line);
        }
        file.close();

        parseInput();

        std::cout << findAllPaths() << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}

