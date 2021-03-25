/*

*/


#include <stdio.h>
#include <iostream>


void myfunc(int && val){
    val++;
    std::cout << "val = " << val << std::endl;
}


class MyMoveableClass{
    private:
        int _size;
        int * _data;
    
    public:
        MyMoveableClass(size_t size) {// constructor
            _size = size;
            _data = new int[_size];

            std::cout << "Creating instance of MyMovableClass at address " << this << " allocated with size=" << _size*sizeof(int) << " bytes" <<std::endl;
        }

        
        MyMoveableClass(const MyMoveableClass& mmc){  // copy constructor - deep copy
            _size = mmc._size;
            _data = new int[_size];
            *_data = *mmc._data;
            std::cout << "Copying content of instance " << &mmc << " to instance " << this << std::endl;
        }

        
        MyMoveableClass& operator=(const MyMoveableClass &source){    // assignment operator overload
            std::cout << "Assigning content of instance " << &source << " to instance " << this << std::endl;
            
            if (this == &source){
                return * this;
            }
            delete[] _data;
            _data = new int[source._size];
            *_data = *source._data;
            _size = source._size;
            return *this;
        }

        MyMoveableClass(MyMoveableClass &&source){   // move constructor
            std::cout << "Moving constructor instance "<< &source << " to instance " << this << std::endl;
            _data = source._data;
            _size = source._size;
            source._data = nullptr;
            source._size = 0;
        }


        MyMoveableClass &operator=(MyMoveableClass &&source){  // move assignment operator
            std::cout << "Moving (assign) instance " << &source << " to instance " << this << std::endl;

            if (this == &source){
                return *this;
            }

            delete[] _data;
            _data = source._data;
            _size = source._size;

            source._data = nullptr;
            source._size = 0;
            return *this;
        }

        ~MyMoveableClass(){
            std::cout << "Deleting the instance of MyMovableClass at address " << this << std::endl;
            delete[] _data;
        }
};


void UseMyMovableClass_Object(MyMoveableClass obj){
    std::cout << "Using object " << &obj << std::endl;
}


int main(){
    myfunc(42);

    int i = 30;
    myfunc(std::move(i));

    std::cout << "i=" << i << std::endl;

    size_t a = 10;

    MyMoveableClass obj1(a);   // regular constructor
    MyMoveableClass obj2(20);
    MyMoveableClass obj3(obj1); // copy constructor
    MyMoveableClass obj4 = obj1; // copy assignment operator
    obj4 = obj2; // copy assignment operator

    MyMoveableClass obj5(100); //regular constructor;
    obj5 = MyMoveableClass(1000); // move assignment operator
    MyMoveableClass obj6 = MyMoveableClass(400); // Move constructor

    MyMoveableClass obj7(100);
    UseMyMovableClass_Object(obj7);
    UseMyMovableClass_Object(std::move(obj7)); // using move semantics
}
