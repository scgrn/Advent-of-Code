#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2025/day06/input.txt");

    if (file.is_open()) {
        std::vector<std::string> input;
        std::string line;        
        while (getline(file, line)) {
            input.emplace_back(line);
        }
        file.close();

        int w = input[0].length();
        int h = input.size();

        uint64_t total = 0;
        std::vector<uint64_t> operands;
        for (int x = 0; x < w; x++) {
            char operation;
            if (input[h - 1][x] != ' ') {
                operation = input[h - 1][x];
            }
            
            std::string s;
            for (int y = 0; y < h - 1; y++) {
                if (input[y][x] != ' ') {
                    s += input[y][x];
                }
            }

            if (!s.empty() || x == (w - 1)) {
                uint64_t operand = stoull(s);
                operands.emplace_back(operand);
            }

            if (s.empty() || x == (w - 1)) {
                if (operation == '+') {
                    uint64_t sum = 0;
                    for (auto& operand : operands) {
                        sum += operand;
                    }
                    total += sum;
                } else {
                    uint64_t product = 1;
                    for (auto& operand : operands) {
                        product *= operand;
                    }
                    total += product;
                }
                operands.clear();
            }
        }

        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

