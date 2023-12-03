#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    int sum = 0;
    
    std::string line;
    std::ifstream file("2023/day01/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            std::string firstDigit = line.substr(line.find_first_of("0123456789"), 1);
            std::string lastDigit = line.substr(line.find_last_of("0123456789"), 1);
            
            std::string calibrationValue = firstDigit + lastDigit;

            sum += atoi(calibrationValue.c_str());
        }
        file.close();
    }
    std::cout << sum << "\n";
    
    return 0;
}
