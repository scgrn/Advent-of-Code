#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2024/day01/input.txt");

    if (file.is_open()) {
        std::vector<int> list1;
        std::vector<int> list2;

        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string location1;
            std::string location2;

            ss >> location1;
            ss >> location2;

            list1.push_back(atoi(location1.c_str()));
            list2.push_back(atoi(location2.c_str()));
        }

        std::sort(list1.begin(), list1.end());
        std::sort(list2.begin(), list2.end());

        int total = 0;
        for (int i = 0; i < list1.size(); i++) {
            int diff = abs(list1[i] - list2[i]);
            total += diff;
        }
        std::cout << total << std::endl;

        file.close();
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

