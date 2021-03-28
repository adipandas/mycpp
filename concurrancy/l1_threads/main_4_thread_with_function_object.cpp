/*
 * Build this program as : g++ main_4_thread_with_function_object.cpp -pthread 
*/ 

#include <iostream>
#include <thread>


class Vehicle{
    public:
        void operator()(){
            std::cout << "Vehicle object has been created. \n" << std::endl;
        }
};



class VehicleThreadClass{
    public:
        VehicleThreadClass(int id): _id(id) {}
    
        void operator()(){
            std::cout << "Vehicle #id" << _id << " has been created." << std::endl;
        }
    
    private:
        int _id;
};


int main(){

    // std::thread t(Vehicle());  // C++'s most vexing parse - throws an error as it is ambiguous 
    // t.join();

    std::thread t1( (Vehicle()) );  // add extra parantheses
    std::thread t2 = std::thread( Vehicle() );  // use copy initialization i.e. copy assignment operator
    std::thread t3{ Vehicle() };   // use uniform initialization with braces

    std::cout << "Finish work in main.\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    t1.join();
    t2.join();
    t3.join();

    std::thread t4 = std::thread(VehicleThreadClass(10));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "Finished work in main.\n";
    t4.join();

}
