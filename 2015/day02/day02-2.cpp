#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>

int calculateRibbon(std::vector<int> dims) {
    std::sort(dims.begin(), dims.end());
 
    return dims[0] * 2 + dims[1] * 2 + dims[0] * dims[1] * dims[2];
}

int main(int argc, char* argv[]) {
    std::ifstream file("2015/day02/input.txt");

    if (file.is_open()) {
        int total = 0;

        std::string line;
        while (getline(file, line)) {
            std::vector<int> dims;
            std::stringstream ss(line);
            std::string str;
            while (getline(ss, str, 'x')) {
                dims.push_back(atoi(str.c_str()));
            }
            total += calculateRibbon(dims);
        }
        file.close();

        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

