#include <iostream>
#include <thread>
#include <future>


class Vehicle{
    public:
        Vehicle(): _id(0), _name_ptr(new std::string("Default Name")){
            std::cout << "Vehicle #" << _id << "; Default constructor called" << std::endl;
        }

        Vehicle(int id) : _id(id), _name_ptr(new std::string("Default Name")){
            std::cout << "Vehicle #" << _id << "; Initializing constructor called" << std::endl;
        }

        Vehicle(int id, std::string name) : _id(id), _name_ptr(new std::string(name)){
            std::cout << "Vehicle #" << _id << "; Initializing constructor called" << std::endl;
        }

        Vehicle(Vehicle const &v){  // copy constructor - deep copy
            _id = v._id;
            _name_ptr = new std::string( *(v._name_ptr) );
            std::cout << "Vehicle #" << _id << "; Copy constructor called" << std::endl;
        }

        Vehicle& operator= (Vehicle const &v){ // copy assignment operator - deep copy
            _id = v._id;
            _name_ptr = new std::string ( *(v._name_ptr) );
            std::cout << "Vehicle #" << _id << "; Copy assignment operator called" << std::endl;
        }

        Vehicle(Vehicle &&v){ // move constructor
            _id = v._id;
            _name_ptr = new std::string (*(v._name_ptr));
            std::cout << "Vehicle #" << _id << "; Move constructor called" << std::endl;
        }

        ~Vehicle(){
            delete _name_ptr;
            // std::cout << "Vehicle #" << _id << "; Destructor of vehicle called" << std::endl;
        }

        void ID(int id){ _id = id;}  // setter
        int ID(){return _id;}        // getter

        void Name(std::string name){*_name_ptr = name;}
        std::string Name(){return *_name_ptr;}

    private:
        int _id;
        std::string * _name_ptr;
};



int main(){
    Vehicle v0;    // default constructor
    Vehicle v1(1);   // initializing constructor

    std::future<void> ftr = std::async([](Vehicle v){
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work
        v.ID(2);
    }, v0);

    v0.ID(3);
    ftr.wait();
    std::cout << "Vehicle #" << v0.ID() << std::endl;

    Vehicle v0_; // default constructor
    Vehicle v1_(1, "Car");

    std::future<void> ftr_ = std::async([](Vehicle v){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        v.Name("Vehicle 2");
    }, v0_);
    v0_.Name("Vehicle 3");

    ftr_.wait();
    std::cout << v0_.Name() << std::endl;
}
