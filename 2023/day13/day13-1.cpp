#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdint>

std::vector<std::vector<std::string>> input;

int findMirror(std::vector<std::string> &group) {
    for (int split = 1; split < group.size(); split++) {
        int size = std::min(split, (int)group.size() - split);
        
        bool found = true;
        for (int y = 0; y < size; y++) {
            if (group[split - 1 - y] != group[split + y]) {
                found = false;
            }
        }
        if (found) {
            return split;
        }
    }
    return 0;
}

std::vector<std::string> rotate(std::vector<std::string> &group) {
    std::vector<std::string> ret;

    int width = group[0].length();
    for (int i = 0; i < width; i++) {
        std::string s = "";

        for (int j = 0; j < group.size(); j++) {
            s += group[group.size() - j -1][i];
        }
        
        ret.push_back(s);
    }

    return ret;
}

uint64_t getScore(std::vector<std::string> &group) {
    uint64_t ret = findMirror(group) * 100;
    std::vector<std::string> rotated = rotate(group);
    ret += findMirror(rotated);

    return ret;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2023/day13/input.txt");
    if (file.is_open()) {
        std::vector<std::string> group;
        while (getline(file, line)) {
            if (line.length() == 0) {
                input.push_back(group);
                group.clear();
            } else {
                group.push_back(line);
            }
        }
        input.push_back(group);
        file.close();
        
        uint64_t sum = 0;
        for (auto& group : input) {
            sum += getScore(group);
        }
        std::cout << sum << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}
