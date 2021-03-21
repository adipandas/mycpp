#include <iostream>
#include <string>
#include <vector>

void printGrid(std::vector<std::vector<int>> grid){
    for (auto row: grid){
        for (auto col: row){
            std::cout << col <<" ";
        }
        std::cout<<"\n";
    }
}

int main(){
    std::vector<std::vector<int>> grid {{0, 1, 0, 0, 0, 0}, 
                                        {0, 1, 0, 0, 0, 0},
                                        {0, 1, 0, 0, 0, 0},
                                        {0, 1, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 1, 0}};
    std::cout<<"grid:"<<"\n";
    printGrid(grid);

}
