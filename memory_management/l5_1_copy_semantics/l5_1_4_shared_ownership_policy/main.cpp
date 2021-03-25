/*
Shared ownership policy: use counter to track useage of heap memory.

* static members initialized in the class must be const otherwise initialize static members outside the class
*/ 


#include <iostream>


class MyClass{
    private:
        int * _n;
        static int counter;
    
    public:
        MyClass(int value);              // constructor
        MyClass(MyClass &source);        // copy constructor
        MyClass& operator=(MyClass& mc);  // assignment operator overloaded
        ~MyClass();                      // destructor
};


int MyClass::counter = 0;


MyClass::MyClass(int value){
    _n = (int *) malloc(sizeof(int));
    *_n = value;
    ++counter;
    std::cout << "Resource allocated at address " << _n << std::endl;
}


MyClass::MyClass(MyClass & mc){
    this->_n = mc._n;
    ++counter;
    std::cout <<  counter << " instances with handles to address " << _n << " with value=" << *_n << " in the HEAP" << std::endl;
}


MyClass& MyClass::operator=(MyClass &mc){
    this->_n = mc._n;
    ++counter;
    return *this;
}


MyClass::~MyClass(){
    --counter;
    if (counter == 0){
        free(_n);
        std::cout << "Resource freed at address " << _n << std::endl;
    } else {
        std::cout << "Instance at address " << this << " goes out of scope with counter reduced to " << counter << std::endl;
    }
}


int main(){
    MyClass source(42);  // allocation
    MyClass destination1(source);   // sharing allocated memory
    MyClass destination2 = source;  //sharing allocated memory
}
