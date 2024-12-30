#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

int calculatePaper(int w, int h, int l) {
    int area1 = l * w;
    int area2 = w * h;
    int area3 = h * l;
    int slack = std::min(std::min(area1, area2), area3);

    return 2 * area1 + 2 * area2 + 2 * area3 + slack;
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
            total += calculatePaper(dims[0], dims[1], dims[2]);
        }
        file.close();

        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

