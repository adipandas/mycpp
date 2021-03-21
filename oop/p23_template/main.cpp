#include "template_example.h"
#include "template_example.cpp"

int main(){
    int a = 2, b =3;

    std::vector<int> simpleVector{1,2,3};

    std::cout << "a * b  = " << Product<int>(a, b) << std::endl;

    std::cout << "max(a, b) = " << Max<int>(a, b) << std::endl;

    std::cout << "Average(a, b) = (a+b)/2 = " << Average<int>(a, b) << std::endl;
    
    PrintVector<float>(std::vector<float>{0, 2, 3, 4});

    std::cout << "Before scaling: ";
    PrintVector<int>(simpleVector);
    Scale<int, std::vector<int>>(4, simpleVector);
    std::cout<<"After scaling by 4: ";
    PrintVector<int>(simpleVector);
}
