#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>


enum class State {kEmpty, kObstacle, kPath, kGoal, kVisited, kStart};
const int delta[4][2] {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};       // possible set of actions


std::string CellStateToString(State s){
    std::string out;

    switch (s)
    {
    case State::kEmpty:
        out = "0   ";
        break;
    case State::kObstacle:
        out = "🏔️   ";
        break;
    case State::kPath:
        out = "🚗   ";
        break;
    case State::kGoal:
        out = "🏡   ";
        break;
    case State::kVisited:
        out = "❌   ";
        break;
    case State::kStart:
        out = "🚦   ";
        break;
    default:
        out = "❓   ";
        break;
    }
    return out;
}


std::vector<State> ParseGridStringToRow(std::string row){
    std::vector<State> current_row;
    std::istringstream iss(row);
    int i;
    char c;

    while (iss >> i >> c && c==','){
        if (i == 0){
            current_row.push_back(State::kEmpty);
        } else if (i == 1){
            current_row.push_back(State::kObstacle);
        }
    }
    return current_row;
}


void ReadGridWorld(std::string const filepath, std::vector<std::vector<State>> &grid){
    std::ifstream grid_file;
    grid_file.open(filepath);

    std::string row_string;
    while(getline(grid_file, row_string)){
        grid.push_back(ParseGridStringToRow(row_string));
    }
}


void PrintGridWorld(std::vector<std::vector<State>> &grid){
    for (auto row: grid){
        for (auto col: row){
            std::cout << CellStateToString(col);
        }
        std::cout << "\n";
    }
}


int Heuristic(int x1, int y1, int x2, int y2){  // Manhattan distance from one coordinate to another
    return abs(x2 - x1) + abs(y2 - y1);
}


void AddToQueue(int x, int y, int g, int h, std::vector<std::vector <int>> &queue,  std::vector<std::vector<State>> &grid){
    std::vector<int> _tmp {x, y, g, h};
    queue.push_back(_tmp);             // add to the node to the queue
    grid[x][y] = State::kVisited;       // mark as visited
}


bool CompareNodes(std::vector<int> node1, std::vector<int> node2){
    return (node1[2]+node1[3]) > (node2[2]+ node2[3]);
}

bool CellIsValid(int const x, int const y, std::vector<std::vector<State>> const &grid){
    return (x > -1 && y > -1 && x<grid.size() && y < grid[0].size() && grid[x][y]==State::kEmpty);
}


void ExpandToNeighbors(std::vector<int> const &currentNode, std::vector<std::vector<int>> &queue, std::vector<std::vector<State>> &grid, int const goal[2]){
    int nextX, nextY;
    for (int i=0; i<4; i++){
        nextX = currentNode[0] + delta[i][0];
        nextY = currentNode[1] + delta[i][1];

        if (CellIsValid(nextX, nextY, grid)){
            int g = currentNode[2] + 1;
            int h = Heuristic(nextX, nextY, goal[0], goal[1]);

            AddToQueue(nextX, nextY, g, h, queue, grid);
        }
    }
}


std::vector<std::vector <State>> Search(std::vector<std::vector<State>> &grid, const int start[2], const int goal[2]){
    std::vector<std::vector<int>> queue;       // nodes (or queue of nodes) to explore next (a.k.a. buffer)


    int x = start[0], y = start[1];
    int goalX = goal[0], goalY = goal[1];
    int g = 0;
    int h = Heuristic(x, y, goalX, goalY);

    AddToQueue(x, y, g, h, queue, grid);

    while (!queue.empty()){
        std::sort(queue.begin(), queue.end(), CompareNodes);
        auto current_node = queue.back();
        queue.pop_back();

        x = current_node[0], y = current_node[1];
        grid[x][y] = State::kPath;

        if (x == goalX && y == goalY){
            grid[start[0]][start[1]] = State::kStart;
            grid[goal[0]][goal[1]] = State::kGoal;
            return grid; // break while loop
        }
        ExpandToNeighbors(current_node, queue, grid, goal);
    }

    std::cout << "No path found!"<< std::endl;
    return std::vector<std::vector<State>> {};
}


int main(){
    std::string filepath = "./grid.world";
    int start[2] = {0, 0};                      // start coordinates
    int goal[2] = {4, 5};                       // destination coordinates
    std::vector<std::vector<State>> grid;
    ReadGridWorld(filepath, grid);
    PrintGridWorld(grid);
    std::vector<std::vector<State>> path = Search(grid, start, goal);
    std::cout << "Path is given by the following:\n";
    PrintGridWorld(path);
}
