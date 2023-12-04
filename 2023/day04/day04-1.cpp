#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

std::vector<int> splitGroup(std::string group) {
    std::vector<int> ret;

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

int calculateScore(std::string line) {
    line = line.substr(line.find(':') + 1);

    int split = line.find('|');
    std::string winningGroup = line.substr(0, split);
    std::string numbersGroup = line.substr(split + 1);

    std::vector<int> winning = splitGroup(winningGroup);
    std::vector<int> numbers = splitGroup(numbersGroup);

    int score = 0;
    for (auto number : numbers) {
        for (auto winningNumber : winning) {
            if (number == winningNumber) {
                if (score == 0) {
                    score = 1;
                } else {
                    score *= 2;
                }
            }
        }
    }
    
    return score;
}

int main(int argc, char* argv[]) {
    int sum = 0;
    
    std::string line;
    std::ifstream file("2023/day04/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            sum += calculateScore(line);
        }
        file.close();
    }
    std::cout << sum << "\n";
    
    return 0;
}

