#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> input;
int width, height;

bool check(int x, int y, int dx, int dy) {
    const std::string key = "XMAS";
    
    //  skip X
    int xp = x + dx;
    int yp = y + dy;

    for (int c = 1; c < key.length(); c++) {
        if (xp >= 0 && xp < width && yp >= 0 && yp < height) {
            if (input.at(yp)[xp] != key[c]) {
                return false;
            }
        } else {
            //  out of bounds
            return false;
        }
        xp += dx;
        yp += dy;
    }

    return true;
}

int search(int x, int y) {
    int matches = 0;

    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx != 0 || dy != 0) {
                if (check(x, y, dx, dy)) {
                    matches++;
                }
            }
        }
    }

    return matches;
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
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (input.at(y)[x] == 'X') {
                    total += search(x, y);
                }
            }
        }
        
        std::cout << total << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}
