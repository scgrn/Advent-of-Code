#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>

std::vector<std::string> input;
int width, height;

void roll() {
    for (int x = 0; x < width; x++) {
        for (int y = 1; y < height; y++) {
            if (input[y][x] == 'O') {
                int yPos = y;
                while (yPos > 0 && input[yPos - 1][x] == '.') {
                    yPos--;
                }
                input[y][x] = '.';
                input[yPos][x] = 'O';
            }
        }
    }
}

int64_t count() {
    int64_t sum = 0;

    for (int y = 0; y < height; y++) {
        int count = 0;
        for (int x = 0; x < width; x++) {
            if (input[y][x] == 'O') {
                count++;
            }
        }
        sum += (count * (height - y));
    }

    return sum;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2023/day14/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            input.push_back(line);
        }
        file.close();
        
        width = input[0].size();
        height = input.size();

        roll();
        std::cout << count() << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}
