#include <iostream>
#include <vector>

int addInts(int a, int b){
    return a + b;
}

void printVector1Dints(std::vector<int> a){
    for (int i : a){
        std::cout << i <<" ";
    }
}

int sumVector1dInts(std::vector<int> a){
    int c = 0;
    for (int i: a){
        c+=i;
    }
    return c;
}

int main(){
    int a = 1;
    int b = 2;

    int c = addInts(a, b);
    std::cout<<"Add a{" << a <<"} and b{"<<b<<"} to get c{"<<c<<"}\n";

    std::vector<int> x{1,2,3,4,55};
    std::cout<<"Sum of vector{ ";
    printVector1Dints(x);
    std::cout<<"} is " << sumVector1dInts(x) <<"\n";
}
