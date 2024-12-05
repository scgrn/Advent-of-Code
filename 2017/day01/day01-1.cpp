#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
    std::ifstream file("2017/day01/input.txt");
    if (file.is_open()) {
        std::string input;
        getline(file, input);
        file.close();

        int total = 0;
        for (int i = 0; i < input.length(); i++) {
            int next = (i + 1) % input.length();
            if (input[i] == input[next]) {
                total += input[next] - '0';
            }
        }
        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

