/*
* Check memory allocation sequence.

* Check memory leaks in code using valgrind: 
``valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=./valgrind_out.txt ./a.out``

*/

#include <iostream>
#include <stdlib.h>


class MyClass{
    public:
        MyClass(){
            std::cout << "Constructor called.\n";
        }

        ~MyClass(){
            std::cout << "Destructor called.\n";
        }

        void * operator new[](size_t size){
            std::cout << "new: Allocating " << size << " bytes of memory." << std::endl;
            void *p = malloc(size);
            return p;
        }

        void operator delete[](void *p){
            std::cout << "delete: Memory freed." << std::endl;
            free(p);
        }

    private:
        int _number;
};


int main(){
    MyClass *p = new MyClass[10]();
    delete[] p;   // comment this line for trial with valgrind
}
