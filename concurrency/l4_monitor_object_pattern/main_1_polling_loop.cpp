/*
* Polling loop example: Not the best way. Queue is not completely emptied by the program end

Build using command: g++ main_1_polling_loop.cpp -pthread

*/


#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <future>
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
        std::mutex _mutex;
        int _nVehicles;

    public:
        WaitingVehicles():_nVehicles(0){}

        bool DataAvailable(){
            std::lock_guard<std::mutex> lg(_mutex);   // lock mutex
            return !_vehicles.empty();                // read shared memory
        }

        int NumVehicles(){
            std::lock_guard<std::mutex> lg(_mutex);
            return _nVehicles;
        }

        Vehicle PopBack(){
            // vector modification under lock
            std::lock_guard<std::mutex> lg(_mutex);     // lock mutex
            
            // make changes to shared memory
            Vehicle v = std::move(_vehicles.back());   // read last element of vector
            _vehicles.pop_back();                      // pop (remove) last element of vector

            _nVehicles -= 1;
            return v;                                 // will not be copied due to return value optimization (RVO) in C++
        }

        void PushBack(Vehicle &&v){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));  // simulate some work

            std::lock_guard<std::mutex> lg(_mutex);  // acquire mutex lock to make modifications in shared memory

            std::cout  << " Vehicle #" << v.ID() << " will be added to the WaitingVehicles queue" << std::endl;
            _vehicles.emplace_back(std::move(v));
            _nVehicles += 1;
        }
};


int main(){

    // monitor object accessed by multiple threads - shared pointer
    std::shared_ptr<WaitingVehicles> waitingVehiclesQueue(new WaitingVehicles);

    std::cout << "Spawning threads ... " << std::endl;
    std::vector< std::future<void> > futures;
    for (int i=0; i<100; ++i){
        // create a new vehicle instance and move it into waitingVehicleQueue
        Vehicle v(i);
        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::PushBack, waitingVehiclesQueue, std::move(v)));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(2));  // delay between creation and collection

    std::cout << "Collecting results..." << std::endl;
    while(true){
        if (waitingVehiclesQueue->DataAvailable()){
            Vehicle v = waitingVehiclesQueue->PopBack();
            std::cout << "  Vehicle #" << v.ID() << " has been removed from waitingVehicles queue" << std::endl;

            if (waitingVehiclesQueue->NumVehicles()<=0){
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                break;
            }
        }
    }

    std::for_each(futures.begin(), futures.end(), [](std::future<void> &f){f.wait();});

    std::cout << "Finished processing Waiting Vehicles Queue" << std::endl;

    std::cout << "Number of Vehiles left in the waitingVehiclesQueue: " << waitingVehiclesQueue->NumVehicles() << std::endl;
    
    return 0;
}
