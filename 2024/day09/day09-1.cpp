#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <vector>

std::vector<int> disk;

void visualize() {
    for (int i : disk) {
        if (i == -1) {
            std::cout << ". ";
        } else {
            std::cout << i << ' ';
        }
    }
    std::cout << std::endl;
}

void uncompress(std::string diskMap) {
    for (int digit = 0; digit < diskMap.length(); digit++) {
        int count = diskMap[digit] - '0';
        if (digit % 2 == 0) {
            for (int i = 0; i < count; i++) {
                disk.emplace_back(digit / 2);
            }
        } else {
            for (int i = 0; i < count; i++) {
                disk.emplace_back(-1);
            }
        }
    }
}

void defrag() {
    int lastBlock = disk.size() - 1;
    
    for (int i = 0; i < disk.size(); i++) {
        if (disk[i] == -1) {
            while (disk[lastBlock] == -1) {
                lastBlock--;
            }
            if (i < lastBlock) {
                disk[i] = disk[lastBlock];
                disk[lastBlock] = -1;
            }
        }
    }
}

uint64_t calculateChecksum() {
    uint64_t sum = 0;
    
    for (int i = 0; i < disk.size(); i++) {
        if (disk[i] != -1) {
            sum += i * disk[i];
        }
    }
    
    return sum;
}

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day09/input.txt");
    std::string line;
    std::string diskMap;

    if (file.is_open()) {
        while (getline(file, line)) {
            diskMap = line;
        }
        file.close();

        uncompress(diskMap);
        defrag();
        std::cout << calculateChecksum() << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}
