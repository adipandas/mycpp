#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <algorithm>


class Vehicle{
    public:
        Vehicle(int id) : _id(id){}

    private:
        int _id;
};


class WaitingVehicles{
    public:
        WaitingVehicles(): _tmpVehicles(0){}

        void PrintSize(){
            std::cout << "#vehicles = " << _tmpVehicles << std::endl;
        }

        void PushBack(Vehicle &&v){   // typical behavior

            // vehicles.push_back(std::move(v)); // data race would cause an exception

            int oldNum = _tmpVehicles;
            std::this_thread::sleep_for(std::chrono::microseconds(1)); // wait delibrately to expose data race
            _tmpVehicles = oldNum + 1;
        }

    private:
        int _tmpVehicles;
        std::vector<Vehicle> _vehicles;  // list of all vehicles waiting on intersection
};


int main(){
    std::shared_ptr<WaitingVehicles> waitingVehiclesQueue(new WaitingVehicles);
    std::vector< std::future<void> > futures;

    for (size_t i=0; i < 1000; ++i){
        Vehicle v(i);

        futures.emplace_back(
            std::async(std::launch::async, &WaitingVehicles::PushBack, waitingVehiclesQueue, std::move(v))
            );  // asynchronous policy - data race and _tmpVehicles will be used simulatneously by many

        // futures.emplace_back(
        //     std::async(std::launch::deferred, &WaitingVehicles::PushBack, waitingVehiclesQueue, std::move(v))
        //     );   // synchronous policy - no data race
    }

    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr){
        ftr.wait();
    });

    waitingVehiclesQueue->PrintSize();   //(data race) - not all vehicles added to this queue when done asynchronously
}
