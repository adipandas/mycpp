/*

Compile using the command: g++ main_5_lambda_functions.cpp -pthread

*/


#include <iostream>
#include <thread>


int main(){
    int id = 0;

    // auto f0 = [](){ std::cout << "ID = " <<  id << std::endl;} ;  // error: cannot access id in lambda function local scope
    
    
    id++;
    auto f1 = [id](){std::cout << "ID = " << id << std::endl;} ; // pass id variable to lambda function by value in ``capture list []``

    id++;
    auto f2 = [&id](){ std::cout << "ID = " << id << std::endl;} ;  // pass-by-reference to lambda function scope from the outer scope.

    // auto f3 = [id](){ std::cout << "ID = " << ++id << std::endl;} ;  // error id may not be modified

    auto f4 = [id]() mutable { std::cout << "ID = " << id << std::endl;} ;  // pass-by-value to lambda function with mutable keyword- makes id value mutable in local scope

    f1();
    f2();
    f4();


    // example of first creation of function object and then passing the parameter later
    auto f5 = [](const int i) {std::cout << "ID = " << i << std::endl;} ; // function object creation

    f5(id);


    int i = 0;
    auto lmbd1 = [&i](){std::cout << "a) i in lambda = " << i << std::endl;};  // capture by reference (immutable)

    auto lmbd2 = [i]() mutable {std::cout << "b) i in lambda = " << ++i << std::endl;};   // capture-by-value (mutable)

    lmbd2();  // calling closure and executing the lambda

    std::cout << "c) i in main = " << i << std::endl;

    auto lmbd3 = [&i]() mutable {std::cout << "d) i in lambda = " << ++i << std::endl;};   // capture-by-reference (mutable)
    lmbd3();
    std::cout << "e) i in main = " << i << std::endl;

    auto lmbd4 = [](const int i){ std::cout << "f) i in lambda = " << i << std::endl;};  // pass by value parameter
    lmbd4(++i);

    // observe the effect of capturing by reference at an earlier point in time.
    lmbd1();


    // THREADING ESXPERIMENTS

    int j = 0; // define a variable

    // starting first thread using lambda (pass by reference)
    auto func1 = [&j] () {
        std::this_thread::sleep_for(std::chrono::microseconds(100));
        std::cout << "a) j in thread (call-by-reference) = " << j << std::endl;
    };

    std::thread t1(func1);


    // starting a second thread (by value)
    std::thread t2( [j]() mutable {
        std::this_thread::sleep_for(std::chrono::microseconds(50));
        std::cout << "b) j in Thread (call-by-value) = " << j << std::endl;
    });

    // increament and print j in main
    ++ j;
    std::cout << "c) j in main (call-by-value) = " << j << std::endl;

    // wait for threads before returning
    t1.join();
    t2.join();
}
