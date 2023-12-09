#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

struct Location {
    std::string left, right;
};

std::vector<std::string> input;
std::string directions;
std::string currentLocation;
std::unordered_map<std::string, Location> map;

void parseInput() {
    directions = input.at(0);

    for (int i = 2; i < input.size(); i++) {
        std::string line = input.at(i);
        
        Location location;
        location.left = line.substr(7, 3);
        location.right = line.substr(12, 3);
        map.emplace(line.substr(0, 3), location);
    }
}

int followDirections() {
    int steps = 0;
    int position = 0;
    currentLocation = "AAA";
    
    while (currentLocation.compare("ZZZ") != 0) {
        char step = directions[position];
        position++;
        if (position >= directions.length()) {
            position = 0;
        }
        
        if (step == 'L') {
            currentLocation = map.at(currentLocation).left;
        } else {
            currentLocation = map.at(currentLocation).right;
        }
        steps++;
    }
    
    return steps;
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

        int steps = followDirections();
        std::cout << steps << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}

