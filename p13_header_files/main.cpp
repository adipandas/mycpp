#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#endif

#include "my_first_header.h"
#include <iostream>

void InnerFunction(int i){
    std::cout << "Inside inner function. " << i << "\n";
}

void OuterFunction(int i){
    std::cout << "Inside outer function. "<< i<< "\n";
    InnerFunction(i);
}

int IncrementAndComputeVectorSum(std::vector<int> v){
    int total = 0;
    AddOneToEach(v);

    for (auto i: v){
        total += i;
    }
    return total;
}

void AddOneToEach(std::vector<int> &v){
    for (auto& i: v){
        i += 1;
    }
}

int main(){
    int a = 1;
    int b = 2;

    OuterFunction(a);
    InnerFunction(b);

    std::vector<int> v{1,2,3,4};
    std::cout << "Original Vector: ";
    for (auto e: v){
        std::cout << e << " ";
    }
    std::cout << "\n";

    AddOneToEach(v);
    std::cout << "Add 1 to Vector: ";
    for (auto e: v){
        std::cout << e << " ";
    }
    std::cout << "\n";

    std::cout << "Sum of vector: " << IncrementAndComputeVectorSum(v) <<"\n";

}
