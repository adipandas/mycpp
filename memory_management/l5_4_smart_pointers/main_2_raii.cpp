/*
Automatic allocation and deallocation of memory on the heap with RAII (Resource allocation Is Initailization)
*/

#include <iostream>


class MyInt{
    int *_p;  // heap data pointer

    public:
        MyInt(int *p=NULL) {_p = p;}

        ~MyInt(){
            std::cout << "resource " << *_p << " deallocated" << std::endl;
            delete _p;
        }

        int &operator *() {return *_p;}  // overload dereferencing operator
};


int main(){
    double denominator[] = {1.0, 2.0, 3.0, 4.0, 5.0};

    for (size_t i = 0; i < 5; i++){
        //allocate resource on the stack
        MyInt numerator_ptr(new int(i));

        std::cout << *numerator_ptr << "/" << denominator[i] << " = " << *numerator_ptr/denominator[i] << std::endl;
    }
}
