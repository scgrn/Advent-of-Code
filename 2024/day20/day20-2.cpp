#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>

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
    int cost;
    bool solid;
    Vec2 source;
};
std::vector<std::vector<Node>> grid;
int width, height;

std::vector<Node> path;
Vec2 start, goal;

std::vector<Vec2> cheatDeltas;

struct CompareNode {
    bool operator() (Node const& a, Node const& b) const {
        return a.cost > b.cost;
    }
};

inline int manhattanDistance(Vec2 const& a, Vec2 const& b) {
    return (abs(a.x - b.x) + abs(a.y - b.y));
}

void constructCheatDeltas(int steps) {
    for (int y = -steps; y <= steps; y++) {
        for (int x = -steps; x <= steps; x++) {
            int distance = manhattanDistance(Vec2{x, y}, Vec2{0, 0});
            if (distance >= 2 && distance <= steps) {
                cheatDeltas.emplace_back(Vec2{x, y});
            }
        }
    }
}

void initGrid(std::vector<std::string> const& map) {
    width = map[0].length();
    height = map.size();

    for (int y = 0; y < height; y++) {
        std::vector<Node> row;
        for (int x = 0; x < width; x++) {
            Node node;
            node.cost = INT_MAX;
            node.pos = Vec2{x, y};
            if (map[y][x] == '#') {
                node.solid = true; 
            } else {
                node.solid = false;
                if (map[y][x] == 'S') {
                    start = Vec2{x, y};
                }
                if (map[y][x] == 'E') {
                    goal = Vec2{x, y};
                }
            }
            row.emplace_back(node);
        }
        grid.emplace_back(row);
    }
}

void search() {
    std::priority_queue<Node, std::vector<Node>, CompareNode> frontier;
   
    grid[start.y][start.x].cost = 0;
    grid[start.y][start.x].source = start;
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
            
            if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                if (!grid[newY][newX].solid) {
                    int newCost = current.cost + 1;

                    if (newCost < grid[newY][newX].cost) {
                        grid[newY][newX].cost = newCost;
                        grid[newY][newX].source = current.pos;
                        frontier.push(grid[newY][newX]);
                    }
                }
            }
        }
    }
    
    Node current = grid[goal.y][goal.x];
    path.emplace_back(current);
    while (current.pos.x != start.x || current.pos.y != start.y) { 
        Vec2 source = grid[current.pos.y][current.pos.x].source;
        current = grid[source.y][source.x];
        path.emplace_back(current);
    }
}

int countCheats() {
    int total = 0;

    for (auto& pos : path) {
        for (auto& delta : cheatDeltas) {
            int nx = pos.pos.x + delta.x;
            int ny = pos.pos.y + delta.y;

            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                if (!grid[ny][nx].solid) {
                    int newCost = pos.cost + manhattanDistance(delta, Vec2{0, 0});;
                    if (grid[ny][nx].cost - newCost >= 100) {
                        total++;
                    }
                }
            }
        }
    }

    return total;
}

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day20/input.txt");

    if (file.is_open()) {
        std::string line;
        std::vector<std::string> map;

        while (getline(file, line)) {
            map.emplace_back(line);
        }
        file.close();

        initGrid(map);
        constructCheatDeltas(20);
        search(); 

        std::cout << countCheats() << std::endl;
   } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

