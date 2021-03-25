/*
No options for converting away from shared pointers. 
Once you have created a shared pointer, you must stick to it (or a copy of it) for the remainder of your program.

Raw pointer can be extracted from a shared (or unique) pointer.
However, this operation does not decrease the reference count within shared pointer.
This means that calling delete on the raw pointer in the last line of code inside main() will 
generate a runtime error as a resource is trying to be deleted which is managed by shared pointer and has already been removed.
The output of the program when compiled with g++ thus is: malloc: *** error for object 0x1003001f0: pointer being freed was not allocated.
*/ 

#include <iostream>
#include <memory>


int main(){
    
    // construct unique pointer
    std::unique_ptr<int> uniqueptr1(new int);
    
    // shared pointer from unique pointer
    std::shared_ptr<int> sharedptr1 = std::move(uniqueptr1);

    // weak pointer from shared pointer
    std::weak_ptr<int> weakptr1(sharedptr1);

    // shared pointer from weak pointer    
    std::shared_ptr<int> sharedptr2 = weakptr1.lock();

    // Uncommenting below lines will throw errors as explained in the comments above.
    // raw pointer from shared (or unique pointer)
    // int *raw_ptr1 = sharedptr2.get();
    // delete raw_ptr1;
    //
    // std::unique_ptr<int> uniqueptr2(new int);
    // int *raw_ptr2 = uniqueptr2.get();
    // delete raw_ptr2;
}
