/*
To build this code, run the following in terminal: g++ main_5_6_variadic_templates_threads.cpp -pthread
*/

#include <iostream>
#include <string>
#include <thread>


void printID(int id){
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "ID = " << id << std::endl;
}


void printNameAndID(std::string name, int id){
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Name: " << name << "; ID="<< id << std::endl;
}


void printName(std::string name, int waitTime){
    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
    std::cout << "Name: " << name << std::endl;
}

namespace ns1
{
    void printName(std::string &name, int waitTime){
        std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
        name += " (from Thread)";
        std::cout << name << std::endl;
    }

} // namespace name


class Vehicle{
    public:
        Vehicle(): _id(0) {}
        
        Vehicle(int id): _id(id) {}

        void AddID (int id) {_id = id;}

        void SetName(std::string name) { _name=name; }

        void printName() { std::cout << "Name = " << _name << std::endl; }

        void printID () { std::cout << "Vehicle ID = " << _id << std::endl; }

    private:
        int _id;
        std::string _name;
};


int main(){
    int id = 10;

    std::thread t1(printID, id);
    std::thread t2(printNameAndID, "Ad", ++id);

    t1.join();
    t2.join();


    std::string name1 = "Name1";
    std::string name2 = "Name2";

    std::thread t3(printName, name1, 100);              // thread with value copy of ``name1``
    std::thread t4(printName, std::move(name2), 100);   // thread with move semantics of ``name2``

    t3.join(); 
    t4.join();

    std::cout << "name1 (for Main) = " << name1 << std::endl;   // name1 is copied by value above
    std::cout << "name2 (for Main) = " << name2 << std::endl;   // name2 is moved using std::move, thus will be empty at this line.

    std::string name3 ("My Thread");
    std::thread t5(ns1::printName, std::ref(name3), 50); // starting thread with reference arguments
    t5.join();

    name3 += " (from Main)";
    std::cout << name3 << std::endl;

    Vehicle v1, v2;
    std::thread t6 = std::thread(&Vehicle::AddID, v1, 1);    // call member function on the object v1 by value
    std::thread t7 = std::thread(&Vehicle::AddID, &v2, 2);   // call member function on the object v2 by reference

    t6.join();
    t7.join();

    v1.printID();
    v2.printID();


    // Object should outlive the completion of the thread if its method is passed by reference.
    // otherwise there will be an attempt to access an invalidated memory address. 
    // An alternative is to use a heap-allocated object and a reference-counted 
    // pointer such as std::shared_ptr<Vehicle> to ensure that 
    // the object lives as long as it takes the thread to finish its work.

    std::shared_ptr<Vehicle> v3(new Vehicle);
    std::thread t8 = std::thread(&Vehicle::AddID, v3, 10); // call memberfunction on object v3
    t8.join();

    v3->printID();

    std::shared_ptr<Vehicle> v4 (new Vehicle);
    std::thread t9 = std::thread(&Vehicle::SetName, v4, "Ad");
    std::thread t10 = std::thread(&Vehicle::AddID, v4, 40);
    t9.join();
    t10.join();
    v4->printID();
    v4->printName();
}
