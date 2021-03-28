#include <iostream>
#include <thread>
#include <future>
#include <memory>


class Vehicle{
    public:
        Vehicle(): _id(0), _name_ptr(new std::string("Default Name")){
            std::cout << "Vehicle #" << _id << "; Default constructor called" << std::endl;
        }

        Vehicle(int id, std::string name) : _id(id), _name_ptr(new std::string(name)){
            std::cout << "Vehicle #" << _id << "; Initializing constructor called" << std::endl;
        }

        Vehicle(Vehicle &&v): _name_ptr(std::move(v._name_ptr)){ // move constructor
            _id = v.ID();
            std::cout << "Vehicle #" << _id << "; Move constructor called" << std::endl;
        }

        void ID(int id){ _id = id;}  // setter
        int ID(){return _id;}        // getter

        void Name(std::string name){*_name_ptr = name;}
        std::string Name(){return *_name_ptr;}

    private:
        int _id;
        std::unique_ptr<std::string> _name_ptr;
};



int main(){
    Vehicle v0; // default constructor
    Vehicle v1(1, "Car"); // initializing constructor


    std::future<void> ftr = std::async([](Vehicle v){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        v.Name("Vehicle 2");
    }, std::move(v0));
    // v0.Name("Vehicle 3");  // error as unique pointer is moved to the thread

    ftr.wait();
    // std::cout << v0.Name() << std::endl; // error as unique pointer is moved to the thread
}
