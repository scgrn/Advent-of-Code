#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day05/testInput.txt");
    std::string line;

    std::unordered_map<int, std::vector<int>> rules;
    std::vector<std::vector<int>> updates;
    
    if (file.is_open()) {
        while (getline(file, line)) {
            if (!line.empty()) {
                if (line[2] == '|') {
                    int page1 = atoi(line.substr(0, 2).c_str());
                    int page2 = atoi(line.substr(3, 2).c_str());
                    std::cout << page1 << " | " << page2 << std::endl;
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
            for (int i = 0; i < update.size(); i ++) {
                std::cout << update[i] << ",";
            }
            std::cout << std::endl;
        }
        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

