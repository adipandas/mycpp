/*
- Add data to a vector using .push_back()
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


std::vector<int> parseLine(std::string const s){
    std::istringstream iss(s);
    std::vector<int> v;

    int i;          // buffer for integer
    char c;         // buffer for comma
    
    while (iss >> i >> c){
        v.push_back(i);
    }
    return v;
}


void readGridWorldFile(std::string const filename, std::vector<std::vector<int>> &a){
    std::cout << "Started reading GridWorld File..." << "\n";
    std::ifstream my_file;
    my_file.open(filename);

    std::string my_line;
    int n; 
    char c;

    int i = 0;
    while (std::getline(my_file, my_line)){
        a.push_back(parseLine(my_line));
        i++;
    }
    std::cout << "Finished reading GridWorld!" << "\n";
}

void printGridWorld(std::vector<std::vector<int>> grid){
    for (auto row: grid){
        for (auto col: row){
            std::cout << col << " ";
        }
        std::cout << "\n";
    }
}


int main(){
    std::string filepath = "./grid.world";    
    std::vector<std::vector<int>> grid;

    readGridWorldFile(filepath, grid);
    
    printGridWorld(grid);
}
