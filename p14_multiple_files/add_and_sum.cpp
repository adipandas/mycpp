#include "add_one.h"

int AddAndSum(std::vector<int> v){
    AddOne(v);
    int sum = 0;
    for (int i: v){
        sum += i;
    }
    return sum;
}
