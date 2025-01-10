#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2018/day01/input.txt");

    if (file.is_open()) {
        std::unordered_map<int, bool> visited;
        std::vector<int> list;

        while (getline(file, line)) {
            std::stringstream ss(line);
            list.emplace_back(atoi(line.c_str()));
        }
        file.close();

        int pos = 0;
        int index = 0;
        while (true) {
            pos += list[index];

            if (visited.find(pos) != visited.end()) {
                std::cout << pos << std::endl;
                return 0;
            }
            visited.emplace(pos, true);

            index++;
            if (index >= list.size()) {
                index = 0;
            }
        }
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

