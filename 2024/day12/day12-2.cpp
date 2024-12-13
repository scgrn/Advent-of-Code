#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> map;
int width, height;

struct Region {
    char type;
    int area;
    int sides;
};
std::vector<Region> regions;

//  lookup into regions vector by coordinate
std::vector<int> regionIndex;

char checkMap(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return map[y][x];
    } else {
        return ' ';
    }
}

int checkCorner(int x, int y) {
    struct{
        int dx, dy;
    } const dirs[] = {
        { 0, -1},
        { 1,  0},
        { 0,  1},
        {-1,  0}
    };

    int corners = 0;
    
    char c = map[y][x];
    for (int dir = 0; dir < 4; dir++) {
        int nextDir = (dir + 1) % 4;
        bool match1 = checkMap(x + dirs[dir].dx, y + dirs[dir].dy) == c;
        bool match2 = checkMap(x + dirs[nextDir].dx, y + dirs[nextDir].dy) == c;
        
        //  convex corner
        if (!match1 && !match2) {
            corners++;
        }
        
        //  concave corner
        if (match1 && match2) {
            int dx = dirs[dir].dx + dirs[nextDir].dx;
            int dy = dirs[dir].dy + dirs[nextDir].dy;
            
            if (checkMap(x + dx, y + dy) != c) {
                corners++;
            }
        }
    }
    
    return corners;
}

void flood(int x, int y, Region &region) {
    regionIndex[y * width + x] = regionIndex.size();
    region.area++;
    region.sides += checkCorner(x,y);

    if (y > 0) {
        if (map[y - 1][x] == region.type && regionIndex[(y - 1) * width + x] == -1) {
            flood(x, y - 1, region);
        }
    }
    if (y < height - 1) {
        if (map[y + 1][x] == region.type && regionIndex[(y + 1) * width + x] == -1) {
            flood(x, y + 1, region);
        }
    }
    if (x > 0) {
        if (map[y][x - 1] == region.type && regionIndex[y * width + x - 1] == -1) {
            flood(x - 1, y, region);
        }
    }
    if (x < width - 1) {
        if (map[y][x + 1] == region.type && regionIndex[y * width + x + 1] == -1) {
            flood(x + 1, y, region);
        }
    }
}

int calculateCost() {
    int total = 0;
    
    for (auto& region : regions) {
        total += region.area * region.sides;
    }
    
    return total;
}

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day12/input.txt");
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            map.push_back(line);
        }
        file.close();

        width = map[0].length();
        height = map.size();

        regionIndex.assign(width * height, -1);
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (regionIndex[y * width + x] == -1) {
                    Region region;
                    region.type = map[y][x];
                    region.area = 0;
                    region.sides = 0;
                    flood(x, y, region);
                    regions.emplace_back(region);
                }
            }
        }

        std::cout << calculateCost() << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}
