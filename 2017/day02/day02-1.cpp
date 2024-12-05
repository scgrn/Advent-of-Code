#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

int main(int argc, char* argv[]) {
    std::ifstream file("2017/day02/input.txt");
    int sum = 0;

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            int largest = -1;
            int smallest = std::numeric_limits<int>::max();

            std::stringstream ss(line);
            std::string str;
            while (getline(ss, str, '\t')) {
                int number = atoi(str.c_str());
                if (number > largest) {
                    largest = number;
                }
                if (number < smallest) {
                    smallest = number;
                }
            }
            
            sum += (largest - smallest);
        }
        file.close();

        std::cout << sum << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

