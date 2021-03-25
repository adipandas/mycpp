/*
Unique pointers: Allocate memory on the heap and auto deallocate the memory when unique pointers go out of scope.
Unique pointers are themselves allocated on stack.
Default choice of pointers with C++.
Available in std lib c++
More or less unique pointers work like raw pointers. (Examples below)
Can be used by including <memory> in the code.
*/ 


#include <iostream>
#include <memory>
#include <string>


void RawPointer(){
    int *raw_ptr = new int;  // create a raw ponter on the heap
    std::cout << "Resource allocated using raw pointer.\n";
    * raw_ptr = 1;  // assign value to the heap memory
    delete raw_ptr;  // delete the resource on the heap after use.
    std::cout << "Resource deallocated by calling delete on Raw pointer.\n";
}


void UniquePointerExample(){
    std::unique_ptr<int> unique_int_ptr (new int); // Create a unique pointer on the stack
    std::cout << "Resource allocated with smart pointer. \n";
    *unique_int_ptr = 2;  // use the unique pointer

    // delete is not necessary; resource will be deallocated when the unique pointer goes out of scope.
    std::cout << "Resource deallocated but no need to call `delete` explicitly.\n";
}


class MyClass{
    private:
        std::string _text;
    
    public:
        MyClass(){
            std::cout << "Created object at address " << this << std::endl;
        }

        MyClass(std::string text){
            _text = text;
            std::cout << "Created object at address " << this << std::endl;
        }

        ~MyClass(){
            std::cout << "Object with address " << this << " and string <" <<_text << "> destroyed " << std::endl;
        }

        void Text(std::string _t){
            _text = _t;
        }

        std::string Text(){ return _text; }
};


int main(){
    RawPointer();
    UniquePointerExample();

    std::unique_ptr<MyClass> mc1 (new MyClass());
    mc1->Text("Instance 1 setter.");   // using member function similar to raw pointers

    std::unique_ptr<MyClass> mc2 (new MyClass("Hello"));

    std::cout << "Objects (smart pointers) have stack addresses "  << mc1.get() << " and " << mc2.get() << std::endl;

    *mc1 = *mc2;                       // using dereference operator and copying one class into another (copy assignment operator) (deep copy in this case as no heap memory allocated for any member variables)


}
