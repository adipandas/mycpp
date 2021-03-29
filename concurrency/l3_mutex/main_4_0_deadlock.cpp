// build using the command : g++ main_4_0_deadlock.cpp -pthread

#include <iostream>
#include <thread>
#include <mutex>
 
std::mutex mutex1, mutex2;
 
void ThreadA()
{
    // Creates deadlock problem
    mutex2.lock();                              // mutex 2 acquired by thread A
    std::cout << "Thread A" << std::endl;
    mutex1.lock();                              // mutex 1 acquired by thread A
    mutex2.unlock();                            // mutex 2 unlocked by A
    mutex1.unlock();                            // mutex 1 unlocked by A
}
 
void ThreadB()
{
    // Creates deadlock problem
    mutex1.lock();                              // mutex 1 locked by B
    std::cout << "Thread B" << std::endl;       
    mutex2.lock();                              // mutex 2 locked by B
    mutex1.unlock();                            // mutex 1 unlocked by B
    mutex2.unlock();                            // mutex 2 unlocked by B
}
 
void ExecuteThreads()
{
    /* DEAD LOCK 
    t1 - cannot acquire mutex 1 and thus waiting (stuck) with mutex 2
    t2 - cannot acquire mutex 2 and thus waiting (stuck) with mutex 1
    */

    std::thread t1( ThreadA );  // acquire mutex 2 and then acquired 1
    std::thread t2( ThreadB );  // acquire mutex 1 and then acquired 2
 
    t1.join();  // starts with mutex 2 and waits for locking 1 (locked by thread t2)
    t2.join();  // starts with mutex 1 and waits for locking 2 (locked by thread t1)
 
    std::cout << "Finished" << std::endl;
}

 
int main()
{
    ExecuteThreads();
    return 0;
}
