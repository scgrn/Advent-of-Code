#include <iostream>
#include <fstream>
#include <sstream>

#include "md5.cpp"

int main(int argc, char* argv[]) {
    std::ifstream file("2015/day04/input.txt");

    if (file.is_open()) {
        std::string input;
        getline(file, input);
        file.close();

        long test = 0L;
        bool found = false;
        while (!found) {
            std::string hash = hashing::md5::sig2hex(hashing::md5::hash(input + std::to_string(test)));
            if (hash.rfind("000000", 0) == 0) {
                std::cout << test << std::endl;
                found = true;
            } else {
                test++;
            }
        }
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }
    return 0;
}
