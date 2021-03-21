/*
This code uses all the previous learned tools to print a beautiful GridWorld in console.
Grid is parsed as vector<vector <int>>
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>


enum class State {kEmpty, kObstacle};

std::string cellString(State s){
    std::string out;

    switch(s){
        case State::kEmpty:
            out = "0   ";
            break;
        case State::kObstacle:
            out = "⛰️   ";
            break;
    }

    return out;
}


State cellState(int a){
    if (a == 1){
        return State::kObstacle;
    } else if (a == 0){
        return State::kEmpty;
    }
}

void printGridWorld(std::vector<std::vector<int>> grid){
    for (auto row: grid){
        for (auto col: row){
            std::cout << cellString(cellState(col));
        }
        std::cout << "\n";
    }
}

std::vector<int> parseGridStringToRow(std::string row){
    std::vector<int> row_vector;

    std::istringstream ss(row);

    int n;
    char c;
    
    while (ss >> n >> c && c == ','){
        row_vector.push_back(n);
    }
    return row_vector;
}

void readGridWorldFile(std::string const filepath, std::vector<std::vector<int>> &grid){
    std::ifstream my_file;
    my_file.open(filepath);
    std::string line_buffer;
    while (std::getline(my_file, line_buffer)){
        grid.push_back(parseGridStringToRow(line_buffer));
    }
}

int main(){
    std::string filepath = "./grid.world";
    std::vector<std::vector<int>> grid;

    readGridWorldFile(filepath, grid);
    printGridWorld(grid);
}
