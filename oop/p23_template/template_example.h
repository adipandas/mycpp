#include <iostream>
#include <cassert>
#include <vector>


template <typename T>
T Product(T a, T b);


template <typename T>
T Max(T a, T b);


template <typename Type>
Type Average(Type a, Type b);


template <typename Type>
void PrintVector(std::vector<Type>);


template <typename T1, typename T2>
void Scale(T1 num, T2 & container);

