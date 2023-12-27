#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>

const int MAX_STEPS = 3;
const int MIN_STEPS = 1;

struct Node {
    uint64_t heatLoss;
    int x, y;
    bool horiz;
};

struct Offset {
    int dx, dy;
};

class Compare {
    public:
        bool operator() (Node node1, Node node2) {
            return node1.heatLoss > node2.heatLoss;
        }
};

std::vector<std::string> map;
int height, width;

std::priority_queue<Node, std::vector<Node>, Compare> queue;
std::unordered_map<std::string, bool> visited;

std::vector<Offset> dirOffsets(bool horiz) {
    if (horiz) {
        return {{1, 0}, {-1, 0}};
    } else {
        return {{0, 1}, {0, -1}};
    }
}

std::string createHash(const Node& node) {
    std::stringstream ss;

    ss << node.x << " ";
    ss << node.y << " ";
    ss << (node.horiz ? 1 : 0);

    return ss.str();
}

void addNodes(const Node& node) {
    std::vector<Offset> offsets = dirOffsets(node.horiz);
    
    for (int dir = 0; dir < 2; dir++) {
        uint64_t heatLoss = node.heatLoss;
        for (int i = 1; i <= MAX_STEPS; i++) {
            int x = node.x + (i * offsets[dir].dx);
            int y = node.y + (i * offsets[dir].dy);
        
            if (x >= 0 && x < width && y >= 0 && y < height) {
                heatLoss += (map[y][x] - '0');
                if (i >= MIN_STEPS) {
                    queue.push({heatLoss, x, y, dir == 0});
                } 
            }
        }
    }
}

uint64_t findPath() {
    queue.push({0, 0, 0, true});
    queue.push({0, 0, 0, false});

    while (!queue.empty()) {
        Node current = queue.top();
        queue.pop();
        
        //std::cout << "(" << current.x << ", " << current.y << ") " << current.heatLoss << std::endl;
        
        if (current.x == width - 1 && current.y == height - 1) {
            return current.heatLoss;
        }

        std::string hash = createHash(current);
        if (visited.find(hash) == visited.end()) {
            visited.emplace(hash, true);
            addNodes(current);
        }
    }
    
    return 0;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream file("2023/day17/input.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            map.push_back(line);
        }
        file.close();

        width = map[0].length() - 1;
        height = map.size();

        std::cout << findPath() << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }    
    
    return 0;
}
