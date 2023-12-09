#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <limits>
#include <queue>

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
    uint64_t start;
    uint64_t end;
    int64_t offset;
};

struct Range {
    uint64_t start;
    uint64_t end;
};

std::vector<std::string> input;

std::vector<Mapping> mappings[7];
std::queue<Range> *inputs, *outputs;

void readSeedRanges(std::string line) {
    line = line.substr(line.find(':') + 1);

    std::stringstream ss(line);
    std::string number;
    std::vector<int64_t> numbers;
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
        int64_t size = numbers.at(i * 2 + 1);
        range.end = range.start + size - 1;

        inputs->push(range);
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
        int64_t dest, source, range;
        
        std::stringstream ss((*it));
        std::string number;
        
        getline(ss, number, ' ');
        dest = std::stoull(number);

        getline(ss, number, ' ');
        source = std::stoull(number);

        getline(ss, number, ' ');
        range = std::stoull(number);

        mapping.start = source;
        mapping.end = source + range - 1;
        mapping.offset = dest - source;
        
        mappings.push_back(mapping);
        it++;
    }
}

void transform() {
    for (int stage = 0; stage < 7; stage++) {
        while (!inputs->empty()) {
            Range range = inputs->front();
            inputs->pop();
            
            bool matched = false;
            for (auto mapping : mappings[stage]) {
                //  check range overlap
                if (range.start <= mapping.end && mapping.start <= range.end) {
                    matched = true;
                    
                    if (range.start < mapping.start) {
                        Range newRange;
                        newRange.start = range.start;
                        newRange.end = mapping.start - 1;
                        inputs->push(newRange);
                        
                        range.start = mapping.start;
                    }

                    if (range.end > mapping.end) {
                        Range newRange;
                        newRange.start = mapping.end + 1;
                        newRange.end = range.end;
                        inputs->push(newRange);
                        
                        range.end = mapping.end;
                    }
                    
                    //  adjust working range
                    range.start += mapping.offset;
                    range.end += mapping.offset;
                    outputs->push(range);
                    
                    break;
                }
            }
            
            if (!matched) {
                outputs->push(range);
            }
        }
        
        if (stage < 6) {
            std::queue<Range> *temp = inputs;
            inputs = outputs;
            outputs = temp;
        }
    }
}

int64_t findLowestLocationNumber() {
    transform();

    uint64_t lowest = std::numeric_limits<int64_t>::max();
    while (!outputs->empty()) {
        Range range = outputs->front();
        outputs->pop();
        lowest = std::min(range.start, lowest);
    }

    return lowest;
}

int main(int argc, char* argv[]) {
    inputs = new std::queue<Range>();
    outputs = new std::queue<Range>();
    
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
        std::cout << findLowestLocationNumber() << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    delete inputs;
    delete outputs;
    
    return 0;
}
