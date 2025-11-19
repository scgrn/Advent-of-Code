#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2020/day01/input.txt");

    if (file.is_open()) {
        std::vector<int> input;

        while (getline(file, line)) {
            input.emplace_back(stoi(line));
        }
        file.close();

        for (int i = 0; i < input.size() - 2; i++) {
            for (int j = i + 1; j < input.size() - 1; j++) {
                for (int k = j + 1; k < input.size(); k++) {
                    if (input[i] + input[j] + input[k]== 2020) {
                        std::cout << input[i] * input[j] * input[k] << std::endl;
                        break;
                    }
                }
            }
        }
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

