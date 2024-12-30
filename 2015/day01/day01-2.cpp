#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
   std::ifstream file("2015/day01/input.txt");

    if (file.is_open()) {
        int floor = 0;
        int pos = 1;
        std::string line;
        while (getline(file, line)) {
            for (char c : line) {
                if (c == '(') {
                    floor++;
                }
                if (c == ')') {
                    floor--;
                    if (floor < 0) {
                        break;
                    }
                }
                pos++;
            }
        }
        file.close();

        std::cout << pos << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

