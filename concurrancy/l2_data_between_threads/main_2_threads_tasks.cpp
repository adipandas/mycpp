#include <iostream>
#include <thread>
#include <future>
#include <memory>
#include <cmath>


double DivideByNumber(double num, double denom){
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Worker thread id = " << std::this_thread::get_id() << std::endl;

    if (denom==0){
        throw std::runtime_error("Exception in thread. Division by zero!");
    }

    return num/denom;
}


int main(){
    // use async to start a task instead of using threads with promise and future
    double num=42.0, denom=0.;

    std::future<double> ftr = std::async(DivideByNumber, num, denom);

    try{
        double result = ftr.get();
        std::cout << "Result = " << result << std::endl;
    } catch (std::runtime_error e){
        std::cout << e.what() << std::endl;
    }

    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

    // launching async with single thread
    double n=4., d=3;
    std::future<double> ftr2 = std::async(std::launch::deferred, DivideByNumber, n, d);
    try{
        double r = ftr2.get();
        std::cout << "Result2 = " << r << std::endl;
    } catch (std::runtime_error e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;
}
