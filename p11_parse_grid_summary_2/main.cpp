/*
This code uses all the previous learned tools to print a beautiful GridWorld in console.
Grid is parsed as vector<vector <State>>
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

enum class State {kEmpty, kObstacle};


std::vector<State> parseGridStringToRow(std::string row){
    std::vector<State> row_vector;
    std::istringstream ss(row);
    int n;
    char c;
    while (ss >> n >> c && c == ','){
        if (n==1){
            row_vector.push_back(State::kObstacle);
        } else {
            row_vector.push_back(State::kEmpty);
        }
    }
    return row_vector;
}

void readGridWorldFile(std::string const filepath, std::vector<std::vector<State>> &grid){
    std::ifstream my_file;
    my_file.open(filepath);
    std::string line_buffer;
    while (std::getline(my_file, line_buffer)){
        grid.push_back(parseGridStringToRow(line_buffer));
    }
}

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

void printGridWorld(const std::vector<std::vector<State>> &grid){
    for (auto row: grid){
        for (auto col: row){
            std::cout << cellString(col);
        }
        std::cout << "\n";
    }
}

int main(){
    std::string filepath = "./grid.world";
    std::vector<std::vector <State>> grid;

    readGridWorldFile(filepath, grid);
    printGridWorld(grid);
}
