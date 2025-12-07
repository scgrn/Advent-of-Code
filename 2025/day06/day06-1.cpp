#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <sstream>

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2025/day06/input.txt");

    if (file.is_open()) {
        std::vector<std::vector<std::string>> tokens;
        std::string input;        
        while (getline(file, input)) {
            std::vector<std::string> line;
            std::stringstream ss(input);
            std::string token;

            while (ss >> token) {
                line.emplace_back(token);
            }            
            tokens.emplace_back(line);
        }

        uint64_t total = 0;
        for (int i = 0; i < tokens[0].size(); i++) {
            uint64_t result;
            if (tokens[tokens.size() - 1][i] == "+") {
                result = 0;
                for (int j = 0; j < tokens.size() - 1; j++) {
                    result += stoull(tokens[j][i]); 
                }
            } else {
                result = 1;
                for (int j = 0; j < tokens.size() - 1; j++) {
                    result *= stoull(tokens[j][i]);
                }
            }
            total += result;
        }
        std::cout << total << std::endl;
        
        file.close();
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

