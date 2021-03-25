/*
Runtime error.
Double deallocation of the heap allocated memory.
Memory is deallocated twice for the same adressed on the HEAP from the two class instances.
*/


#include<iostream>

class MyClass{
    private:
        int * _number;
    
    public:
        MyClass(){  // constructor
            _number = (int *) malloc(sizeof(int));      // allocate memory on heap
        }

        ~MyClass(){  // destructor
            // if (!_number) {free(_number);}  // one safe way to avoid crash due to double deallocation of same memory space.
                free(_number);      // free or deallocate memory on heap
            // _number = nullptr;
            // std::cout << _number << std::endl;
        }

        void PrintOwnAddress(){
            std::cout << "Own Address on stack:" << this << std::endl;
        }

        void PrintHeapMemberAddress(){
            std::cout << "Memory addresss used to manage HEAP memory block: " << _number << std::endl;
        }

};


int main(){
    MyClass mc;
    mc.PrintOwnAddress();
    mc.PrintHeapMemberAddress();

    // copy mc object using default constructor
    MyClass mc2(mc);
    mc2.PrintOwnAddress();
    mc2.PrintHeapMemberAddress();
}