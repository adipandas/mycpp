// Avoid deadlock by proper mutex lock and unlock order in main_4_0_deadlock.cpp
// Avoid such a deadlock: number all resources and require that processes request resources
// only in strictly increasing (or decreasing) order.
// Build using the command: g++ main_4_1_deadlock_remove.cpp -pthread

#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1, mutex2;

void ThreadA()
{
    // Solves deadlock problem
    mutex1.lock();
    std::cout << "Thread A" << std::endl;
    mutex2.lock();
    mutex1.unlock();
    mutex2.unlock();
}

void ThreadB()
{
    // Solves deadlock problem
    mutex1.lock();
    std::cout << "Thread B" << std::endl;
    mutex2.lock();

    mutex1.unlock();
    mutex2.unlock();
}

void ExecuteThreads()
{
    std::thread t1( ThreadA );
    std::thread t2( ThreadB );

    t1.join();
    t2.join();

    std::cout << "Finished" << std::endl;
}

int main()
{
    ExecuteThreads();

    return 0;
}
