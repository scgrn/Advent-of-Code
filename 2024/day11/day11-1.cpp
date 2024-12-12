#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <list>

std::list<uint64_t> blink(std::list<uint64_t> const& stones, int i) {
    std::list<uint64_t> ret;
    
    for (auto& stone: stones) {
        if (stone == 0L) {
            ret.push_back(1L);
        } else {
            std::string str = std::to_string(stone);
            if (str.length() % 2 == 0) {
                std::string str1 = str.substr(0, str.length() / 2);
                std::string str2 = str.substr(str.length() / 2, str.length() / 2);
                ret.push_back(std::stol(str1));
                ret.push_back(std::stol(str2));
            } else {
                ret.push_back(stone * 2024L);
            }
        }
    }
    
    return ret;
}

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day11/input.txt");
    std::string line;
    std::list<uint64_t> stones;
    
    if (file.is_open()) {
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string str;
            while (getline(ss, str, ' ')) {
                stones.push_back(std::stol(str));
            }
        }
        file.close();

        for (int i = 0; i < 25; i++) {
            stones = blink(stones, i);
        }
        
        std::cout << stones.size() << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

