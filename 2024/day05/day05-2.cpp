#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cmath>

std::unordered_map<int, std::vector<int>> rules;
std::vector<std::vector<int>> updates;

bool checkRules(int page1, int page2) {
    if (rules.find(page2) != rules.end()) {
        for (int i = 0; i < rules[page2].size(); i++) {
            if (rules[page2][i] == page1) {
                return false;
            }
        }
    }

    return true;
}

bool checkOrder(std::vector<int> update) {
    for (int i = 0; i < update.size(); i ++) {
        for (int j = 0; j < update.size(); j ++) {
            if (i != j) {
                if (i < j) {
                    if (!checkRules(update[i], update[j])) {
                        return false;
                    }
                } else {
                    if (!checkRules(update[j], update[i])) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

void sort(std::vector<int> &update) {
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i = 1; i < update.size(); i++) {
            if (checkRules(update[i - 1], update[i])) {
                int temp = update[i - 1];
                update[i - 1] = update[i];
                update[i] = temp;
                swapped = true;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day05/input.txt");
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (!line.empty()) {
                if (line[2] == '|') {
                    int page1 = atoi(line.substr(0, 2).c_str());
                    int page2 = atoi(line.substr(3, 2).c_str());
                    rules[page1].push_back(page2);
                } else {
                    std::vector<int> update;
                    std::stringstream ss(line);
                    std::string str;
                    while (getline(ss, str, ',')) {
                        update.push_back(atoi(str.c_str()));
                    }
                    updates.push_back(update);
                }
            }
        }
        file.close();
        
        int total = 0;
        for (auto update : updates) {
            if (!checkOrder(update)) {
                sort(update);
                total += update[floor(update.size() / 2)];
            }
        }
        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

