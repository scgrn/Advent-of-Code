#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2025/day05/input.txt");

    if (file.is_open()) {
        struct Range {
            uint64_t min, max;
        };
        std::vector<Range> ranges;
        
        int total = 0;
        
        bool readingRanges = true;
        while (getline(file, line)) {
            if (readingRanges) {
                if (line.empty()) {
                    readingRanges = false;
                } else {
                    Range range;

                    int hyphenPos = line.find('-');
                    range.min = stoull(line.substr(0, hyphenPos));
                    range.max = stoull(line.substr(hyphenPos + 1));

                    ranges.emplace_back(range);
                }
            } else {
                uint64_t id = stoull(line);
                for (auto& range : ranges) {
                    if (id >= range.min && id <= range.max) {
                        total++;
                        break;
                    }
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

