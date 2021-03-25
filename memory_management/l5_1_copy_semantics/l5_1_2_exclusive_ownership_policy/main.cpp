/*
Delete reference from one object and activate its copy to avoid the conflict.
*/

#include<iostream>


class MyClass{
    private:
        int * _number;

    public:
        MyClass(){
            _number = (int *) malloc(sizeof(int));
            std::cout << "Resource allocated.\n";
        }

        ~MyClass(){
            free(_number);
            std::cout << "Resource freed.\n";
        }

        MyClass(MyClass & mc){
            this->_number = mc._number;
            mc._number = nullptr;
        }

        MyClass &operator=(MyClass & mc){
            this->_number = mc._number;
            mc._number = nullptr;

            return *this;
        }
};


int main(){
    MyClass source;
    MyClass destination1(source);
    MyClass destination2 = source;
}
