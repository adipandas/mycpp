#include <iostream>
#include <future>
#include <mutex>
#include <memory>
#include <thread>
#include <vector>
#include <algorithm>


class Vehicle{
    public:
        Vehicle(int id): _id(id){}

    private:
        int _id;
};


class WaitingVehicles{
    private:
        std::mutex _mutex;
        std::vector<Vehicle> _vehicles;

    public:
        WaitingVehicles(){}

        void PrintSize(){
            _mutex.lock();
            std::cout << "#vehicles = " << _vehicles.size() << std::endl;
            _mutex.unlock();
        }

        void PushBack(Vehicle &&v){
            _mutex.lock();
            _vehicles.emplace_back(std::move(v));  // data race would cause an exception but mutex avoids it
            _mutex.unlock();
        }
};


int main(){
    std::shared_ptr<WaitingVehicles> waitingVehiclesQueue(new WaitingVehicles);
    std::vector< std::future<void> > futures;

    for (size_t i=0; i<1000; ++i){
        Vehicle v(i);
        futures.emplace_back(
            std::async(std::launch::async, &WaitingVehicles::PushBack, waitingVehiclesQueue, std::move(v))
            );
    }

    std::for_each(futures.begin(), futures.end(), [](std::future<void> &f){f.wait();});
    
    waitingVehiclesQueue->PrintSize();
}
