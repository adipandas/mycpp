#include <iostream>
#include <memory>


int main(){
    std::shared_ptr<int> shared1(new int);
    std::cout << "Shared pointer count = " << shared1.use_count() << std::endl;

    std::weak_ptr<int> weakptr1(shared1);
    std::weak_ptr<int> weakptr2(weakptr1);

    std::cout << "Shared pointer count = " << shared1.use_count() << std::endl;

    // std::weak_ptr<int> weakptr_temp (new int);  // COMPILE ERROR - weak pointer can be created using shared_ptr or another weak_ptr

    std::shared_ptr<int> shared2(new int);
    std::weak_ptr<int> weakptr3(shared2);
    shared2.reset(new int);

    if (weakptr3.expired()){
        std::cout << "Weak pointer at address " << &weakptr3 << " has expired."<< std::endl;
    }

}
