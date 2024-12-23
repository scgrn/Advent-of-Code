#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
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
    bool solid;
    int costSoFar;
    int dir;
};
std::vector<std::vector<Node>> graph;
int width, height;

struct Reindeer {
    Vec2 pos;
    int dir;
} reindeer;

Vec2 goal;

struct CompareNode {
    bool operator() (Node const& a, Node const& b) const {
        return a.costSoFar > b.costSoFar;
    }
};

void findReindeerAndGoal(std::vector<std::string> const& map) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y][x] == 'S') {
                reindeer.pos = Vec2{x, y};
                reindeer.dir = 0;
            }
            if (map[y][x] == 'E') {
                goal.x = x;
                goal.y = y;
            }
        }
    }
}

void buildGraph(std::vector<std::string> const& map) {
    for (int y = 0; y < height; y++) {
        std::vector<Node> row;
        for (int x = 0; x < width; x++) {
            Node node;
            node.pos = Vec2{x, y};
            node.dir = -1;
            node.solid = (map[y][x] == '#');
            node.costSoFar = INT_MAX;
            row.emplace_back(node);
        }
        graph.emplace_back(row);
    }
}

void search() {
    std::priority_queue<Node, std::vector<Node>, CompareNode> frontier;
    
    graph[reindeer.pos.y][reindeer.pos.x].costSoFar = 0;
    graph[reindeer.pos.y][reindeer.pos.x].dir = reindeer.dir;
    frontier.push(graph[reindeer.pos.y][reindeer.pos.x]);
    
    while (!frontier.empty()) {
        Node current = frontier.top();
        frontier.pop();

        if (current.pos.x == goal.x && current.pos.y == goal.y) {
            break;
        }
        
        for (int dir = 0; dir < 4; dir++) {
            int newX = current.pos.x + dirs[dir].x;
            int newY = current.pos.y + dirs[dir].y;
            
            if (!graph[newY][newX].solid) {
                int turnCost = (current.dir != dir) ? 1000 : 0;
                int newCost = current.costSoFar + 1 + turnCost;

                if (newCost < graph[newY][newX].costSoFar) {
                    graph[newY][newX].costSoFar = newCost;
                    graph[newY][newX].dir = dir;
                    frontier.push(graph[newY][newX]);
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    std::ifstream file("2024/day16/input.txt");

    if (file.is_open()) {
        std::vector<std::string> map;
        std::string line;
        
        while (getline(file, line)) {
            map.emplace_back(line);
        }
        file.close();
        
        width = map[0].length();
        height = map.size();

        findReindeerAndGoal(map);
        buildGraph(map);
        search();

        std::cout << graph[goal.y][goal.x].costSoFar << std::endl;
    } else {
        std::cout << "Couldn't read input!" << std::endl;
    }

    return 0;
}

