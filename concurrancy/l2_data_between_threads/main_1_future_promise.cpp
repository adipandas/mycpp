#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <cmath>
#include <memory>


void PrintName(std::string name){
    std::this_thread::sleep_for(std::chrono::milliseconds(100));   // simulate work
    std::cout << "Thread 1 = " << name << std::endl;
}


void ModifyMessage(std::promise<std::string> &&prms, std::string message){
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // simulate work
    std::string modifyMessage = message + " has been modified";
    prms.set_value(modifyMessage);
}


void ComputeSqrt(std::promise<double> &&p, int input){
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // simulate work
    double output = std::sqrt(input);
    p.set_value(output);   // promise value is set in thread
}


void DivideByNumber(std::promise<double> &&p, double num, double denom){
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    try{
        if (denom==0){
           throw std::runtime_error("Exception from thread: Division by zero!");
        } else {
            p.set_value( num / denom );
        }
    } catch (...) {
        p.set_exception(std::current_exception());
    }
}


int  main(){
    std::string message = "My message";

    std::thread t1(PrintName, message);

    std::thread t2([message](){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));   // simulate work
        std::cout << "Thread 2 = " << message << std::endl;
    });

    t1.join();
    t2.join();


    std::string messageToThread = "My Message";

    // create promise
    std::promise<std::string> prms;

    // create future
    std::future<std::string> ftr = prms.get_future();

    std::thread t3(ModifyMessage, std::move(prms), messageToThread);

    std::cout << "Original Message from main(): " << messageToThread << std::endl;

    // retrieve message via future and print it in console
    std::string messageFromThread = ftr.get();   /// this message is blocked until data is receieved from the promise in thread by set_value()
    std::cout << "Modified message from thread(): " << messageFromThread << std::endl;
    
    t3.join(); // thread barrier


    double inData = 42.0;
    std::promise<double> prms2;
    std::future<double> ftr2 = prms2.get_future();
    std::thread t4(ComputeSqrt, std::move(prms2), inData);
    auto status = ftr2.wait_for(std::chrono::milliseconds(2000)); // NOTE: if time is kept as 1000 milliseconds the result is unavailable

    if (status == std::future_status::ready){
        std::cout << "Result = " << ftr2.get()  << std::endl;
    } else if (status == std::future_status::timeout || status == std::future_status::deferred) {
        std::cout << "Result unavailable." << std::endl;
    }

    t4.join();

    // Example exceptions in threads
    std::promise<double> prms_last;
    std::future<double> ftr_last = prms_last.get_future();    
    double num=40.0;
    double denom=0.;

    std::thread thread_last(DivideByNumber, std::move(prms_last), num, denom);

    try{
        double result = ftr_last.get();
        std::cout << "Result = " << result << std::endl;
    } catch (std::runtime_error e){
        std::cout << e.what() << std::endl;
    }

    thread_last.join();

}
