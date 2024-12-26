#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <climits>

const int GRID_SIZE = 71;
const int STEPS = 1024;

struct Vec2 {
    int x, y;
};

Vec2 dirs[] = {
    { 1,  0},
    { 0,  1},
    {-1,  0},
    { 0, -1}
};

struct Node {
    Vec2 pos;
    bool solid;
    int cost;
};
std::vector<std::vector<Node>> grid;

struct CompareNode {
    bool operator() (Node const& a, Node const& b) const {
        return a.cost > b.cost;
    }
};

void initializeGrid() {
    grid.clear();

    for (int y = 0; y < GRID_SIZE; y++) {
        std::vector<Node> row;
        for (int x = 0; x < GRID_SIZE; x++) {
            Node node;
            node.pos = Vec2{x, y};
            node.solid = false;
            node.cost = INT_MAX;
            row.emplace_back(node);
        }
        grid.emplace_back(row);
    }
}

int search() {
    std::priority_queue<Node, std::vector<Node>, CompareNode> frontier;
   
    Vec2 start = Vec2{0, 0};
    Vec2 goal = Vec2{GRID_SIZE - 1, GRID_SIZE - 1};
     
    grid[start.y][start.x].cost = 0;
    frontier.push(grid[start.y][start.x]);
    
    while (!frontier.empty()) {
        Node current = frontier.top();
        frontier.pop();

        if (current.pos.x == goal.x && current.pos.y == goal.y) {
            break;
        }
        
        for (int dir = 0; dir < 4; dir++) {
            int newX = current.pos.x + dirs[dir].x;
            int newY = current.pos.y + dirs[dir].y;
            
            if (newX >= 0 && newX < GRID_SIZE && newY >= 0 && newY < GRID_SIZE) {
                if (!grid[newY][newX].solid) {
                    int newCost = current.cost + 1;

                    if (newCost < grid[newY][newX].cost) {
                        grid[newY][newX].cost = newCost;
                        frontier.push(grid[newY][newX]);
                    }
                }
            }
        }
    }

    return grid[goal.y][goal.x].cost;
}

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day18/input.txt");

    if (file.is_open()) {
        std::string line;
        std::vector<Vec2> corruption;

        initializeGrid();
        while (getline(file, line)) {
            int commaPos = line.find(',');
            int x = atoi(line.substr(0, commaPos).c_str());
            int y = atoi(line.substr(commaPos + 1, std::string::npos).c_str());
            corruption.emplace_back(Vec2{x, y});
        }
        file.close();
        
        for (int i = 0; i < STEPS; i++) {
             grid[corruption[i].y][corruption[i].x].solid = true;
        }
        
        int index = STEPS;
        while (index < corruption.size()) {
            for (int y = 0; y < GRID_SIZE; y++) {
                for (int x = 0; x < GRID_SIZE; x++) {
                    grid[y][x].cost = INT_MAX;
                }
            }
            grid[corruption[index].y][corruption[index].x].solid = true;
            if (search() == INT_MAX) {
                std::cout << corruption[index].x << "," << corruption[index].y << std::endl;
                break;
            }
            index++;
        }
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

