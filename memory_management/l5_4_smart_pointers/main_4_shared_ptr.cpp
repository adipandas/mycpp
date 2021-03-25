/*
 * Example of how scope can be used.
 * Example of how shared pointers are used and keep track using a counter.
*/

#include <iostream>
#include <memory>


class MyClass{
    public:
        MyClass(){
            std::cout << "Instance of MyClass created at address " << this << std::endl; 
        }

        ~MyClass() { std::cout << "Destructor of MyClass called for address " << this << std::endl; }
};


class MyClassFaulty{
    public:
        MyClassFaulty(){
            std::cout << "Instance of MyClassFaulty created at address " << this << std::endl; 
        }
        ~MyClassFaulty() { std::cout << "Destructor of MyClassFaulty called for address " << this << std::endl; }

        std::shared_ptr<MyClassFaulty> _member;
};


int main(){
    std::shared_ptr <int> shared1(new int);
    std::cout << "Shared pointer count = " << shared1.use_count() << std::endl;
    
    {   // start a scope
        std::shared_ptr <int> shared2 = shared1;
        std::cout << "Shared pointer count = " << shared1.use_count() << std::endl;
    }   // end a scope

    std::cout << "Shared pointer count = " << shared1.use_count() << std::endl;

    std::shared_ptr<MyClass> shared3(new MyClass());
    std::cout << "MyClass Shared pointer count = " << shared3.use_count() << std::endl;

    shared3.reset(new MyClass());
    std::cout << "MyClass Shared pointer count = " << shared3.use_count() << std::endl;

    std::shared_ptr<MyClass> shared4 = shared3;
    std::cout << "MyClass Shared pointer count = " << shared3.use_count() << std::endl;


    std::shared_ptr<MyClassFaulty> shared5(new MyClassFaulty);
    std::shared_ptr<MyClassFaulty> shared6(new MyClassFaulty);

    // Uncomment below lines to create a cyclic issue for shared_ptr. This cycle does not allow the destructor of pointers share5 and share6 to be called. It causes memory leak.
    // shared5->_member = shared6;
    // shared6->_member = shared5;
}
