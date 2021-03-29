/*
 * Build this program as : g++ main_2_thread.cpp -pthread 
*/ 
#include <iostream>
#include <thread>


void ThreadFunction(){
    std::cout << "thread with ThreadFunction() has id=" << std::this_thread::get_id() <<std::endl;

    std::cout << "Starting work 1 in ThreadFunction() thread with id=" << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Finished work 1 in ThreadFunction() thread with id=" << std::this_thread::get_id() << std::endl;

    std::cout << "Starting work 2 in ThreadFunction() thread with id=" << std::this_thread::get_id() <<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Finished work 2 in ThreadFunction() thread with id=" << std::this_thread::get_id() << std::endl;

}

int main(){
    // create thread
    std::thread t(ThreadFunction);
    
    // make use of below line for program to wait before proceeding and thread finish its job.
    // t.join();

    // do something in main() thread
    std::cout << "Starting work 1 in main() thread with id=" << std::this_thread::get_id() << std::endl; 
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    t.join();  // wait for thread to join before proceeeding

    std::cout << "Finished work 1 in main() thread with id=" << std::this_thread::get_id() << std::endl;
    std::cout << "Starting work 2 in main() thread with id=" << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
    std::cout << "Finished work 2 in main() thread with id=" << std::this_thread::get_id() << std::endl;

    std::thread t2(ThreadFunction);
    
    t2.detach();  // detach the thread

    std::cout << "Starting work 3 in main() thread with id=" << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Finished work 3 in main() thred with id=" << std::this_thread::get_id() << std::endl;

}
