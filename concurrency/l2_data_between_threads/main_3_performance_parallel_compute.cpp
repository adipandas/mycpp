#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <vector>
#include <chrono>


void WorkerFunction(int n){
    std::cout << "Worker thread id = " << std::this_thread::get_id() << std::endl;  // worker id

    // perform work
    for ( size_t i = 0; i < n; ++i){
        std::sqrt(123456.789);
    }
}


int main(){
    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;
    
    // start time
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    // launch tasks
    std::vector<std::future<void>> futures;
    // int nLoops = 1e7; 
    // int nThreads = 10;

    int nLoops = 10; 
    int nThreads = 10;

    for (size_t i=0; i< nThreads; ++i){
        // futures.emplace_back(std::async(std::launch::async, WorkerFunction, nLoops));
        futures.emplace_back(std::async(std::launch::deferred, WorkerFunction, nLoops));
    }
    
    // wait for tasks to complete
    for (const std::future<void> &ftr: futures){
        ftr.wait();
    }

    // stop time
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "Execution finished after " << duration <<  " microseconds" << std::endl;
}
