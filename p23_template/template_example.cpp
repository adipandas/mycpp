#include "template_example.h"


template <typename T>
T Product(T a, T b){
    return a*b;
}

template <typename T>
T Max(T a, T b){
    return (a > b)? a: b;
}


template <typename T>
T Average(T a, T b){
    return (a + b)/2;
}


template <typename Type>
void PrintVector(std::vector<Type> v){
    for (Type i: v){
        std::cout << i << " ";
    }
    std::cout <<"\n";
}


template <typename T1, typename T2>
void Scale(T1 num, T2 & container){
    for (auto& i: container){
        i *= num;
    }
}
