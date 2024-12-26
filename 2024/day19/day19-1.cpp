#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

std::vector<std::string> patterns;
std::vector<std::string> designs;
std::unordered_map<std::string, bool> memo;

bool isDesignPossible(std::string const& design) {
    if (memo.find(design) != memo.end()) {
        return memo.at(design);
    }

    if (design.empty()) {
        return true;
    }

    for (auto& pattern : patterns) {
        if (design.rfind(pattern, 0) == 0) {
            std::string remainder = design.substr(pattern.length());
            if (isDesignPossible(remainder)) {
                memo.emplace(design, true);
                return true;
            }
        }
    }

    memo.emplace(design, false);
    return false;
}

int findPossibleDesigns() {
    int total = 0;

    for (auto& design : designs) {
        if (isDesignPossible(design)) {
            total++;
        }
    }

    return total;
}

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day19/input.txt");

    if (file.is_open()) {
        std::string line;
       
        getline(file, line);
        std::stringstream ss(line);
        std::string pattern;
        while (getline(ss, pattern, ',')) {
            int space = pattern.find_last_of(' ');
            if (space != std::string::npos) {
                pattern = pattern.substr(space + 1, std::string::npos);
            }
            patterns.emplace_back(pattern);
        }

        getline(file, line);

        while (getline(file, line)) {
            designs.emplace_back(line);
        }
        file.close();
        
        std::cout << findPossibleDesigns() << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

