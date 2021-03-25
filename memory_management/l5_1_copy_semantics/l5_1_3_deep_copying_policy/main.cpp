/*
Copy everything and make a new instance of heap objects for the copy.

Requires a lot of memory.
*/

#include <iostream>


class MyClass{
    private:
        int * _number;

    public:
        MyClass(){
            _number = (int *) malloc(sizeof(int));
            std::cout << "Memory allocated at address " << _number << std::endl;
        }

        ~MyClass(){
            free(_number);
            std::cout << "Memory deallocated at address " << _number << std::endl;
        }

        MyClass(MyClass &a){ // deep copy constructor
            _number = (int *) malloc(sizeof(int));
            *_number = *(a._number);
            std::cout << "Resource allocated at address " << _number << std::endl;
            std::cout << "            Source at address " << a._number << std::endl;
        }

        MyClass &operator=(MyClass &a){
            _number = (int *) malloc(sizeof(int));
            *_number = *(a._number);
            std::cout << "Resource allocated at address " << _number << std::endl;
            std::cout << "            Source at address " << a._number << std::endl;

            return *this;
        }


};

int main(){

    MyClass a1;
    MyClass a2(a1);
    MyClass a3 = a1;

}