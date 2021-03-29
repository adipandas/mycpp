/*
* Build using: g++ main_7_mutex_lock.cpp -pthread
* Example using the std::lock - avoiding deadlocks
* std::lock ensures mutexes are always locked in same order
*/

#include <iostream>
#include <thread>
#include <mutex>


std::mutex mtx1, mtx2;


void ThreadA(){
    // locks are always executed in same order
    std::lock(mtx1, mtx2);
    
    // mutex `mtx2` which is already locked with std::lock is adopted to lock_guard using std::adopt_lock option
    std::lock_guard<std::mutex> lock2(mtx2, std::adopt_lock);
    std::cout << "Thread A" << std::endl;
    std::lock_guard<std::mutex> lock1(mtx1, std::adopt_lock);
}


void ThreadB(){
    std::lock(mtx1, mtx2);
    std::lock_guard<std::mutex> lock1 (mtx1, std::adopt_lock);
    std::cout << "Thread B" << std::endl;
    std::lock_guard<std::mutex> lock2 (mtx2, std::adopt_lock);
}


void ExecuteThreads(){
    std::thread t1 (ThreadA);
    std::thread t2 (ThreadB);

    t1.join();
    t2.join();

    std::cout << "Finished" <<std::endl;
}


int main(){
    ExecuteThreads();
}
