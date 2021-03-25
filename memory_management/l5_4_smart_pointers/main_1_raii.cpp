/*
Memory on heap:
    - Allocate memory
    - Use memory 
    - Deallocate memory
*/

#include <iostream>


int main(){
    double denominator[] = {1.0, 2.0, 3.0, 4.0, 5.0};

    for (int i; i<5; ++i){
        double *numerator_ptr = new double(i);                  // allocate memory on heap

        std::cout << *numerator_ptr << "/" << denominator[i] << " = " << *numerator_ptr/denominator[i] << std::endl;   // operation with allocated memory
        
        delete numerator_ptr;   // free the memory
    }
}