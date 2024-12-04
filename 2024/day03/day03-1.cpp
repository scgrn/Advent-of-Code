#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <iterator>

int process(std::string const& str) {
    int comma = str.find(',');
    std::string left = str.substr(4, comma - 4);
    std::string right = str.substr(comma + 1, str.length() - (comma + 2));

    return atoi(left.c_str()) * atoi(right.c_str());
}

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day03/input.txt");
    std::string line;

    if (file.is_open()) {
        std::regex pattern(R"(mul\([0-9]+,[0-9]+\))");
        std::smatch matches;
        
        int total = 0;
        
        while (getline(file, line)) {
            auto begin = std::sregex_iterator(line.begin(), line.end(), pattern);
            auto end = std::sregex_iterator();
            
            for (std::sregex_iterator i = begin; i != end; i++) {
                std::smatch match = *i;
                std::string matchStr = match.str();
                total += process(matchStr);
            }
        }
        file.close();
        
        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}
