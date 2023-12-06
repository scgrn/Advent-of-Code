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

std::vector<std::string> input;
std::vector<Mapping> mappings[7];
std::vector<uint64_t> seeds;

void readSeeds(std::string line) {
    line = line.substr(line.find(':') + 1);

    std::stringstream ss(line);
    std::string number;
    while (getline(ss, number, ' ')) {
        //  remove extraneous spaces
        number.erase(std::remove(number.begin(), number.end(), ' '), number.end());
        
        if (number.size() > 0) {
            seeds.push_back(std::stoull(number));
        }
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

uint64_t findMapping(uint64_t input, std::vector<Mapping> &mappings) {
    uint64_t output = input;
    
    for (auto mapping : mappings) {
        if (input >= mapping.source && input < mapping.source + mapping.range) {
            uint64_t diff = mapping.dest - mapping.source;
            output = input + diff;
        }
    }
    
    return output;
}

uint64_t findLowestLocationNumber() {
    uint64_t lowest = std::numeric_limits<uint64_t>::max();
    
    for (auto seed : seeds) {
        uint64_t input = seed;
        for (int i = 0; i < 7; i++) {
            input = findMapping(input, mappings[i]);
        }
        
        lowest = std::min(input, lowest);
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
        
        readSeeds(input.at(0));
        for (int i = 0; i < 7; i++) {
            readMappings(headers[i], mappings[i]);
        }
    }
    
    std::cout << findLowestLocationNumber() << std::endl;
    
    return 0;
}
