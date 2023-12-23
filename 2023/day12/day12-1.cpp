#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <unordered_map>

struct Row {
    std::string springs;
    std::vector<int> groups;
};

std::vector<Row> rows;
std::unordered_map<std::string, int64_t> cache;

void parseRow(std::string line) {
    Row row;
    
    std::stringstream ss(line);    
    ss >> row.springs;
    
    std::string groupString;
    ss >> groupString;
    
    std::stringstream gss(groupString);
    std::string number;
    while (getline(gss, number, ',')) {
        row.groups.push_back(atoi(number.c_str()));
    }
    
    rows.push_back(row);
}

std::string createHash(const Row& row) {
    std::stringstream ss;
    ss << row.springs << " ";
    for (auto v : row.groups) {
        ss << v << " ";
    }
    return ss.str();
}

int64_t count(const Row& row) {
    if (row.groups.empty()) {
        return row.springs.find('#') != std::string::npos ? 0 : 1;
    } else {
        if (row.springs.empty()) {
            return 0;
        }   
        
        bool allOperational = true;
        for (auto c : row.springs) {
            if (c != '.') {
                allOperational = false;
            }
        }
        
        if (allOperational) {
            return 0;
        }
    }
        
    std::string hash = createHash(row);
    auto iter = cache.find(hash);
    if (iter != cache.end()) {
        return iter->second;
    }

    int64_t sum = 0;
    for (int i = 0; i <= row.springs.size(); i++) {
        bool valid = true;
        int blockSize = row.groups.front();
        
        std::string left = row.springs.substr(0, i);
        if (left.find('#') != std::string::npos) {
            valid = false;
        } else {
            std::string block = row.springs.substr(i, blockSize);
            if (block.find('.') != std::string::npos) {
                valid = false;
            }
        }
        
        if ((i + blockSize < row.springs.size() &&
            row.springs[i + blockSize] == '#') || (i + blockSize > row.springs.size())) {
            
            valid = false;
        }

        if (valid) {
            Row croppedRow;
            
            int blockSize = row.groups.front();
            int end = i + blockSize;
            croppedRow.springs = row.springs.substr(end, row.springs.size() - end);
            if (!croppedRow.springs.empty()) {
                croppedRow.springs.erase(croppedRow.springs.begin());
            }

            croppedRow.groups = row.groups;
            croppedRow.groups.erase(croppedRow.groups.begin());
            
            sum += count(croppedRow);
        };
    }
    
    cache.emplace(hash, sum);
    
    return sum;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2023/day12/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            parseRow(line);
        }
        file.close();

        int64_t sum = 0;
        for (auto& row : rows) {
            sum += count(row);
        }
        std::cout << sum << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}

