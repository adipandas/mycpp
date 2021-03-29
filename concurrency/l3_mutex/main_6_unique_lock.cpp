/*
* Build with the following command: g++ main_6_unique_lock.cpp -pthread
* unique_lock : provides support for more advanced mechanisms, such as deferred locking,
                time locking, recursive locking, transfer of lock ownership and use of condition variables.
                It behaves similar to lock_guard but provides much more flexibility, 
                especially with regard to the timing behavior of the locking mechanism.
 */ 

#include <iostream>
#include <mutex>
#include <algorithm>
#include <thread>
#include <future>
#include <vector>


double result;
std::mutex mtx;


void PrintResult(double denom){
    std::cout << "For denom = " << denom << ", the result is " << result << std::endl;
}


void DivideByNumber(double num, double denom){
    try{
        if (denom!=0){

            std::unique_lock <std::mutex> lck(mtx);   // acquire unique lock and do something with shared memory
            
            result = num/denom;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            PrintResult(denom);

            lck.unlock();   // unlock the mutex and do something else outside the lock

            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // work outside the lock

            lck.lock();   // acquire mutex lock again
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // do something else under the lock

        } else {
            throw std::invalid_argument("Exception in thread. Division by zero!");
        }
    } catch(const std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
    }
}


int main(){
    std::vector<std::future<void>> futures;

    for (float i=-5; i<5; ++i){
        futures.emplace_back(std::async(std::launch::async, DivideByNumber, 50.0, i));
    }
    
    std::for_each(futures.begin(), futures.end(), [](std::future<void> &f){f.wait();});
    
}