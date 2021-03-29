#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <future>
#include <algorithm>


double result;
std::mutex mtx;


void PrintResult(double denom){
    std::cout << "For denom = " << denom << ", the result is " << result << std::endl; 
}


void DivideByNumber(double num, double denom){
    
    try{
        if (denom !=0){
            std::lock_guard<std::mutex> lck(mtx);   // acquire lock before changing shared memory
            result = num/denom;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            PrintResult(denom);
        } else {
            throw std::invalid_argument("Exception from thread: Division by Zero!");
        }
    } catch (const std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return;
    }
}


int main(){
    std::vector < std::future<void> > futures;
    for (double i=-5; i<5; ++i){
        futures.emplace_back(std::async(std::launch::async, DivideByNumber, 50.0, i));
    }

    std::for_each(futures.begin(), futures.end(), [](std::future<void> &f){
        f.wait();
    });
}
