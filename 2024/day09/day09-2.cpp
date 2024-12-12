#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <list>

struct Span {
    int id;
    int length;
};
std::list<Span> disk;

void uncompress(std::string diskMap) {
    for (int digit = 0; digit < diskMap.length(); digit++) {
        Span span;
        span.length = diskMap[digit] - '0';
        if (digit % 2 == 0) {
            span.id = digit / 2;
        } else {
            span.id = -1;
        }
        if (span.length > 0) {
            disk.emplace_back(span);
        }
    }
}

void defrag() {
    std::list<Span>::reverse_iterator file;
    std::list<Span>::iterator space;
    
    for (file = disk.rbegin(); file != disk.rend(); file++) {
        if (file->id != -1) {
            for (space = disk.begin(); space != file.base(); space++) {
                if (space->id == -1) {
                    int lengthDiff = space->length - file->length;
                    if (lengthDiff >= 0) {
                        // swap
                        space->id = file->id;
                        space->length = file->length;
                        file->id = -1;
                        
                        if (lengthDiff > 0) {
                            space++;
                            disk.insert(space, Span{-1, lengthDiff});
                        }
                        break;
                    }
                }
            }
        }
    }
}

uint64_t calculateChecksum() {
    uint64_t sum = 0;

    int location = 0;
    for (Span span : disk) {
        if (span.id == -1) {
            location += span.length;
        } else {
            for (int i = 0; i < span.length; i++) {
                sum += location * span.id;
                location++;
            }
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
