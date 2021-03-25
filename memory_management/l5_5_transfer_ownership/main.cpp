#include <iostream>
#include <memory>


class MyClass{
    private:
        int _member;

    public:
        MyClass(int val): _member{val} {}
        
        void PrintVal(){ std::cout << ", Managed object " << this << " with val=" << _member << std::endl;}
};


void TempFunc1(std::unique_ptr<MyClass> ptr){
    std::cout << "unique_ptr " << &ptr;
    ptr->PrintVal();
}


void TempFunc2(std::shared_ptr<MyClass> ptr){
    std::cout << "shared_ptr (reference_count = " << ptr.use_count() << ") " << &ptr;
    ptr->PrintVal();
}


int main(){
    std::unique_ptr<MyClass> unique_ptr1 = std::make_unique<MyClass>(23);
    
    std::cout << "unique_ptr " << &unique_ptr1;
    unique_ptr1->PrintVal();

    // TempFunc1(unique_ptr1);  // throw error: unique pointer is unique and thus copy cannot be made. Therefore, this will throw error
    TempFunc1(std::move(unique_ptr1));  // move the unique pointer using std::move

    if (unique_ptr1){
        unique_ptr1->PrintVal();
    } else {
        std::cout << "Transferred ownership of the unique_ptr1 in function.\n";
    }


    std::shared_ptr<MyClass> shared_ptr1 = std::make_shared<MyClass>(23);
    std::cout << "shared_ptr (reference_count = " << shared_ptr1.use_count() << ") " << &shared_ptr1;
    shared_ptr1->PrintVal();
    
    TempFunc2(shared_ptr1); // no move semantics required

    std::cout << "shared_ptr (reference_count = " << shared_ptr1.use_count() << ") " << &shared_ptr1;
    shared_ptr1->PrintVal();

}
