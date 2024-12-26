#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

std::vector<std::string> patterns;
std::vector<std::string> designs;
std::unordered_map<std::string, long> memo;

long countArrangements(std::string const& design) {
    if (memo.find(design) != memo.end()) {
        return memo.at(design);
    }

    if (design.empty()) {
        return 1;
    }

    long total = 0;
    for (auto& pattern : patterns) {
        if (design.rfind(pattern, 0) == 0) {
            std::string remainder = design.substr(pattern.length());
            total += countArrangements(remainder);
        }
    }

    memo.emplace(design, total);
    return total;
}

long findPossibleDesigns() {
    long total = 0;

    for (auto& design : designs) {
        total += countArrangements(design);
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

