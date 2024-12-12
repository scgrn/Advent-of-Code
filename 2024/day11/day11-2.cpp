#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <vector>
#include <unordered_map>

std::unordered_map<std::string, uint64_t> memo;

std::string createHash(uint64_t stone, int depth) {
    std::stringstream ss;
    ss << stone << " " << depth;

    return ss.str();
}

uint64_t blink(uint64_t stone, int depth) {
    std::string hash = createHash(stone, depth);
    if (memo.find(hash) != memo.end()) {
        return memo[hash];
    }

    if (depth == 0) {
        return 1L;
    }

    if (stone == 0L) {
        memo[hash] = blink(1L, depth - 1);
    } else {
        std::string str = std::to_string(stone);
        if (str.length() % 2 == 0) {
            std::string left = str.substr(0, str.length() / 2);
            std::string right = str.substr(str.length() / 2, str.length() / 2);
            memo[hash] = blink(std::stol(left), depth - 1) + blink(std::stol(right), depth - 1);
        } else {
            memo[hash] = blink(stone * 2024L, depth - 1);
        }
    }

    return memo[hash];
}

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day11/input.txt");
    std::string line;
    std::vector<uint64_t> stones;
    
    if (file.is_open()) {
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string str;
            while (getline(ss, str, ' ')) {
                stones.push_back(std::stol(str));
            }
        }
        file.close();

        uint64_t total = 0L;
        for (uint64_t stone : stones) {
            total += blink(stone, 75);
        }
        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}
