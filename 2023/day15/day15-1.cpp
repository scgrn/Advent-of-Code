#include <iostream>
#include <fstream>
#include <sstream>

int hash(const std::string& code) {
    int currentValue = 0;
    
    for (auto c : code) {
        currentValue += (int)c;
        currentValue *= 17;
        currentValue %= 256;
    }
    
    return currentValue;
}

int main(int argc, char* argv[]) {
    std::ifstream file("2023/day15/input.txt");
    if (file.is_open()) {
        std::string input;
        getline(file, input);
        file.close();
        
        int sum = 0;
        std::stringstream ss(input);
        std::string code;
        while (std::getline(ss, code, ',')) {
            sum += hash(code);
        }

        std::cout << sum << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}
