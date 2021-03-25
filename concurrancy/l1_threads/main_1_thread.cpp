/*
 * To build this code run: g++ main_1_thread.cpp -pthread
 * Without -pthread flag there is compiler error
*/ 

#include <iostream>
#include <string>
#include <thread>


void threadFunction(){  // function working inside a thread
    std::cout << "Started thread with id="<< std::this_thread::get_id() <<std::endl;
    std::cout << "Working in threadFunction() ..." <<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(8000)); // simulate work
    std::cout << "Finished work in thread!! \n";
}


int main(){
    std::cout << "Hello concurrent world from main!"<< std::endl;
    std::cout << "Thread id = " << std::this_thread::get_id() << " for main() thread" << std::endl;

    unsigned int nCores = std::thread::hardware_concurrency();
    std::cout << "This machine supports concurrency with " << nCores << " cores available." << std::endl;

    // create a thread
    std::thread t(threadFunction);
    // do something in main()
    std::cout << "Thread launched and main continues to work..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(6000)); // simulate work in main
    std::cout << "Finished work in main()!!" <<std::endl;

    // wait for thread to finish work
    t.join();


}
