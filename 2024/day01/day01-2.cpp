#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2024/day01/input.txt");

    if (file.is_open()) {
        std::vector<int> list1;
        std::unordered_map<int, int> list2;

        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string location1;
            std::string location2;

            ss >> location1;
            ss >> location2;

            list1.push_back(atoi(location1.c_str()));

            int location2i = atoi(location2.c_str());
            if (list2.find(location2i) == list2.end()) {
                list2[location2i] = 1;
            } else {
                list2[location2i]++;
            }
        }
        file.close();
        
        int total = 0;
        for (int i : list1) {
            if (list2.find(i) != list2.end()) {
                total += list2[i] * i;
            }
        }
        
        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

