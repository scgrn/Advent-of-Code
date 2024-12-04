#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> input;
int width, height;

bool check(int x, int y) {
    std::string diagonals1;
    diagonals1 += input[y - 1][x - 1];
    diagonals1 += input[y + 1][x + 1];

    std::string diagonals2;
    diagonals2 += input[y + 1][x - 1];
    diagonals2 += input[y - 1][x + 1];

    return ((diagonals1 == "MS" || diagonals1 == "SM") && (diagonals2 == "MS" || diagonals2 == "SM"));
}

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day04/input.txt");
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            input.push_back(line);
        }
        file.close();
        
        width = input.at(0).length();
        height = input.size();

        int total = 0;
        for (int y = 1; y < height - 1; y++) {
            for (int x = 1; x < width - 1; x++) {
                if (input.at(y)[x] == 'A') {
                    total += check(x, y);
                }
            }
        }
        
        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}
