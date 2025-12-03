#include <iostream>
#include <fstream>
#include <regex>

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2025/day02/input.txt");

    if (file.is_open()) {
        getline(file, line);
        
        uint64_t total = 0;
        std::stringstream ss(line);
        std::string range;
        std::regex regex(R"(^(\d+)\1+$)");
        while (std::getline(ss, range, ',')) {
            int hyphenPos = range.find('-');
            uint64_t lower = stoull(range.substr(0, hyphenPos));
            uint64_t upper = stoull(range.substr(hyphenPos + 1));
            
            for (uint64_t i = lower; i <= upper; i++) {
                std::string number = std::to_string(i);
                if (std::regex_search(number, regex)) {
                    total += i;
                }
            }
        }        
        std::cout << total << std::endl;
        
        file.close();
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

