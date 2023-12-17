#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <deque>

struct Lens {
    std::string label;
    int focalLength;
};
std::deque<Lens> boxes[256];

int hash(const std::string& code) {
    int currentValue = 0;
    
    for (auto c : code) {
        currentValue += (int)c;
        currentValue *= 17;
        currentValue %= 256;
    }
    
    return currentValue;
}

void process(std::string const& code) {
    if (code[code.length() - 1] == '-') {
        std::string label = code.substr(0, code.length() - 1);

        int box = hash(label);
        for (int i = 0; i < boxes[box].size(); i++) {
            if (label == boxes[box][i].label) {
                boxes[box].erase(boxes[box].begin() + i);
                break;
            }
        }
    } else {
        Lens lens;

        int pos = code.find_first_of('=');
        lens.label= code.substr(0, pos);
        lens.focalLength = atoi(code.substr(pos + 1).c_str());
        
        bool found = false;
        int box = hash(lens.label);
        for (int i = 0; i < boxes[box].size(); i++) {
            if (boxes[box][i].label == lens.label) {
                boxes[box][i].focalLength = lens.focalLength;
                found = true;
                break;
            }
        }

        if (!found) {
            boxes[box].push_back(lens);
        }
    }
}

uint64_t calculateFocusingPower() {
    uint64_t sum = 0;
    
    for (int box = 0; box < 256; box++) {
        for (int lens = 0; lens < boxes[box].size(); lens++) {
            sum += (box + 1) * (lens + 1) * boxes[box][lens].focalLength;
        }
    }
    
    return sum;
}

int main(int argc, char* argv[]) {
    std::ifstream file("2023/day15/input.txt");
    if (file.is_open()) {
        std::string input;
        getline(file, input);
        file.close();
        
        std::stringstream ss(input);
        std::string code;
        while (std::getline(ss, code, ',')) {
            process(code);
        }

        std::cout << calculateFocusingPower() << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}
