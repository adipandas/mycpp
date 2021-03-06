/*
- std::getline() to read each line in istream object.
- std::getline comes for iostream and this function is a part of standard library.
*/

#include <iostream>
#include <fstream>
#include <string>


void readBoardFile(std::string filepath){
    std::ifstream my_file;
    
    my_file.open(filepath);
    
    if (my_file){
        std::string line;
        while (std::getline(my_file, line)){
            std::cout << line << "\n";
        }
    }
}


int main(){
    std::string filepath = "./grid.world";

    readBoardFile(filepath);
}
