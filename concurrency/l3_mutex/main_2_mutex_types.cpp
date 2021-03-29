#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <algorithm>


class Vehicle{
    private:
        int _id;

    public:
        Vehicle(int id): _id(id){}
        int ID(){return _id;}
};


class WaitingVehicles{
    private:
        std::vector<Vehicle> _vehicles;
        std::timed_mutex _mutex;
        int _max_mutex_tries=3;

    public:
        WaitingVehicles(){}

        void PrintSize(){
            _mutex.lock();
            std::cout << "#vehicles = " << _vehicles.size() << std::endl;
            _mutex.unlock();
        }

        void PushBack(Vehicle &&v){
            for (size_t i =0; i<_max_mutex_tries; ++i){
                if (_mutex.try_lock_for(std::chrono::milliseconds(100))){
                    _vehicles.emplace_back(std::move(v));
                    _mutex.unlock();
                    break;
                } else {
                    std::cout << "Error! Vehicle #" << v.ID() << " could not be added to the vector" << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            }
        }
};


int main(){
    
    std::shared_ptr<WaitingVehicles> waitingVehiclesQueue(new WaitingVehicles);
    std::vector<std::future<void>> futures;
    
    for (int i=0; i<1000; ++i){
        Vehicle v(i);
        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::PushBack, waitingVehiclesQueue, std::move(v)));
    }

    std::for_each(futures.begin(), futures.end(), [](std::future<void> &f){f.wait();});
    waitingVehiclesQueue->PrintSize();
}
