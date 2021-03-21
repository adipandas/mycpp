#include "add_and_sum.h"
#include <iostream>


int main(){
    std::vector<int> a{1,2,3,4,5};

    std::cout << "Orignal vector: ";
    for (auto i: a){
        std::cout << i << " ";
    }
    std::cout <<"\n";

    std::cout << "Add 1 to each element and sum the vector: "<< AddAndSum(a) << "\n";
}
