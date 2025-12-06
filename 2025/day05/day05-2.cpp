#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <algorithm>

struct Range {
    uint64_t min, max;
};

static inline bool cmp(Range const& a, Range const& b) {
    return a.min < b.min;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2025/day05/input.txt");

    if (file.is_open()) {
        std::vector<Range> ranges;
        
        while (getline(file, line) && !line.empty()) {
            Range range;

            int hyphenPos = line.find('-');
            range.min = stoull(line.substr(0, hyphenPos));
            range.max = stoull(line.substr(hyphenPos + 1));

            ranges.emplace_back(range);
        }

        sort(ranges.begin(), ranges.end(), cmp);
      
        std::vector<Range> mergedRanges;
        mergedRanges.push_back(ranges[0]);

        for (int i = 1; i < ranges.size(); i++) {
            Range& last = mergedRanges.back();
            Range& current = ranges[i];

            if (current.min <= last.max) {
                last.max = std::max(last.max, current.max);
            } else {
                mergedRanges.emplace_back(current);
            }
        }

        uint64_t total = 0;
        for (auto& range : mergedRanges) {
            total += (range.max - range.min + 1);
        }
        std::cout << total << std::endl;
        
        file.close();
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

