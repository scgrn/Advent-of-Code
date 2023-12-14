#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdint>

const int SMUDGE_TARGET = 1;    // set to 0 to run part 1

std::vector<std::vector<std::string>> input;

int countDifferingCharacters(const std::string& str1, const std::string& str2) {
    int count = 0;
    for (int i = 0; i < str1.length(); i++) {
        if (str1[i] != str2[i]) {
            count++;
        }
    }

    return count;
}

int findMirror(std::vector<std::string> &group) {
    for (int split = 1; split < group.size(); split++) {
        int size = std::min(split, (int)group.size() - split);
        
        int smudgeCount = 0;
        for (int y = 0; y < size; y++) {
            std::string side1 = group[split - 1 - y];
            std::string side2 = group[split + y];
            smudgeCount += countDifferingCharacters(side1, side2);
        }
        if (smudgeCount == SMUDGE_TARGET) {
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
