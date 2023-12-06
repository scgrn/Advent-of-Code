#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>

const std::string headers[7] = {
    "seed-to-soil map:",
    "soil-to-fertilizer map:",
    "fertilizer-to-water map:",
    "water-to-light map:",
    "light-to-temperature map:",
    "temperature-to-humidity map:",
    "humidity-to-location map:"
};

struct Mapping {
    uint64_t dest;
    uint64_t source;
    uint64_t range;
};

struct Range {
    uint64_t start;
    uint64_t size;
};

std::vector<std::string> input;
std::vector<Mapping> mappings[7];
std::vector<Range> seedRanges;
std::vector<Range> ranges;

void readSeedRanges(std::string line) {
    line = line.substr(line.find(':') + 1);

    std::stringstream ss(line);
    std::string number;
    std::vector<uint64_t> numbers;
    while (getline(ss, number, ' ')) {
        //  remove extraneous spaces
        number.erase(std::remove(number.begin(), number.end(), ' '), number.end());
        
        if (number.size() > 0) {
            numbers.push_back(atol(number.c_str()));
        }
    }
    
    for (int i = 0; i < numbers.size() / 2; i++) {
        Range range;
        range.start = numbers.at(i * 2);
        range.size = numbers.at(i * 2 + 1);

        seedRanges.push_back(range);
    }
}

void readMappings(std::string header, std::vector<Mapping> &mappings) {
    std::vector<std::string>::iterator it = input.begin();
    
    while ((*it) != header && it != input.end()) {
        it++;
    }
    it++;
    
    while ((*it) != "" && it != input.end()) {
        Mapping mapping;
        
        std::stringstream ss((*it));
        std::string number;
        
        getline(ss, number, ' ');
        mapping.dest = std::stoull(number);

        getline(ss, number, ' ');
        mapping.source = std::stoull(number);

        getline(ss, number, ' ');
        mapping.range = std::stoull(number);

        mappings.push_back(mapping);
        it++;
    }
}

void transformRange(Range range, std::vector<Mapping> &mappings) {
    // std::cout << "Range: " << range.start << " - " << range.start + range.size - 1 << std::endl;
    
    for (auto mapping : mappings) {
        uint64_t mappingEnd = mapping.source + mapping.range - 1;
        uint64_t rangeEnd = range.start + range.size - 1;
        
        //  check range overlap
        if (range.start >= mappingEnd or mapping.source >= rangeEnd) {
            //  add start partition
            if (range.start < mapping.source) {
                Range newRange;
                newRange.start = range.start;
                newRange.size = mapping.source - range.start;
                ranges.push_back(newRange);
                
                range.start = mapping.source;
                range.size -= newRange.size;
            }

            //  add end partition
            if (rangeEnd > mappingEnd) {
                Range newRange;
                newRange.start = mappingEnd + 1;
                newRange.size = rangeEnd - mappingEnd + 1;
                ranges.push_back(newRange);
                
                range.size -= mappingEnd - range.start + 1;
            }

            //  adjust working range
            uint64_t diff = mapping.dest - mapping.source;
            range.start += diff;
        }
    }
}

uint64_t findLowestLocationNumber() {
    uint64_t lowest = std::numeric_limits<uint64_t>::max();

    for (auto seedRange : seedRanges) {
        ranges.clear();
        ranges.push_back(seedRange);

        for (int i = 0; i < 7; i++) {
            uint64_t count = 0;
            for (auto range : ranges) {
                transformRange(range, mappings[i]);
                count++;
                std::cout << count << std::endl;
            }
        }

        for (auto range : ranges) {
            lowest = std::min(range.start, lowest);
        }
    }
    
    return lowest;
}


int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2023/day05/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            input.push_back(line);
        }
        file.close();
        
        readSeedRanges(input.at(0));
        for (int i = 0; i < 7; i++) {
            readMappings(headers[i], mappings[i]);
        }
    }
    
    std::cout << findLowestLocationNumber() << std::endl;
    
    return 0;
}
