#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <sstream>
#include <cmath>

uint64_t analyzeDiagram(std::string const& diagram) {
    uint16_t state = 0;
    uint16_t targetState = 0;
    std::vector<uint16_t> buttons;
    
    std::string target = diagram.substr(1, diagram.find(']') - 1);
    for (int i = 0; i < target.length(); i++) {
        if (target[i] == '#') {
            targetState |= (1 << (target.length() - i - 1));
        }
    }

    size_t currentPos = 0;
    while ((currentPos = diagram.find('(', currentPos)) != std::string::npos) {
        std::string buttonStr = diagram.substr(currentPos + 1, diagram.find(')', currentPos) - currentPos - 1);
        currentPos++;

        std::vector<int> lights;
        std::stringstream ss(buttonStr);
        std::string light;
        while (getline(ss, light, ',')) {
            lights.emplace_back(stoi(light));
        }

        uint16_t button = 0;
        for (auto& light : lights) {
            button |= 1 << (target.length() - light - 1);
        }
        buttons.emplace_back(button);
    }
    
    uint64_t lowest = buttons.size();
    int total = std::pow(2, buttons.size());
    for (int mask = 0; mask < total; mask++) {
        uint16_t currentState = 0;
        uint64_t turns = 0;
        for (int i = 0; i < buttons.size(); i++) {
            if (mask & (1 << i)) {
                currentState ^= buttons[i];
                turns++;
            }
        }
        if (currentState == targetState) {
            lowest = std::min(lowest, turns);
        }
    }
    return lowest;
}

int main(int argc, char* argv[]) {
    std::ifstream file("2025/day10/input.txt");

    if (file.is_open()) {
        std::string line;
        std::vector<std::string> input;
        while (getline(file, line)) {
            input.emplace_back(line);
        }
        file.close();

        uint64_t total = 0;
        for (auto& diagram : input) {
            total += analyzeDiagram(diagram);
        }
        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

