/*
* Concurrent message queue
* build using: g++ main.cpp -pthread
*/ 

#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <vector>
#include <algorithm>


class Vehicle{
    private:
        int _id;
    
    public:
        Vehicle(int id):_id(id){}
        int ID(){return _id;}
};


class WaitingVehicles{
    private:
        std::mutex _mutex;
        std::condition_variable _cond;
        std::vector<Vehicle> _vehicles;     // waiting vehicles
    
    public:
        WaitingVehicles(){}   // constructor

        Vehicle PopBack(){
            std::unique_lock<std::mutex> ul(_mutex);   // lock mutex

            // pass unique lock to condition variable - wait if container is empty (_vehicle is empty)
            _cond.wait(ul, [this](){
                return !_vehicles.empty();
            });   // wait - release lock in wait condition, thus shared memory (i.e., _vehicles) can be accessed by other threads

            // other threads can access the lock
            // when wait finishes, we are guarenteed to find new Objects (new elements) in queue

            Vehicle v = std::move(_vehicles.back());  // remove last vector element (new element) from queue
            
            _vehicles.pop_back();
            
            return v;  // after this line, lock will be out of scope and will automatically be released
        }

        void PushBack(Vehicle &&v){
            // std::this_thread::sleep_for(std::chrono::milliseconds(100)); // simulate some work

            std::lock_guard<std::mutex> lg(_mutex);   // acquire lock

            std::cout << " Vehicle #" << v.ID() << " will be added to WaitingVehicleQueue" << std::endl;

            _vehicles.emplace_back(std::move(v));     // push new vehicles in the queue - shared memory modification under the lock

            _cond.notify_one();                       // notify client after pushing new Vehicle into vector
        }
};


int main(){
    std::shared_ptr<WaitingVehicles> waitingVehiclesQueue(new WaitingVehicles);

    std::cout << "Spawning threads... " << std::endl;

    std::vector< std::future<void> > futures;

    for (int i=0; i<10; ++i){

        Vehicle v(i);  // create instance

        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::PushBack, waitingVehiclesQueue, std::move(v)));   // move it to queue
    }

    std::cout << "Collecting results..." << std::endl;
    while (true){

        Vehicle v = waitingVehiclesQueue->PopBack();  // blocked if unique guard is waiting and released when new element is available in the queue

        std::cout << " Vehicle #" << v.ID() << " has been removed from the queue" << std::endl;
    }

    std::for_each(futures.begin(), futures.end(), [](std::future<void> &f){
        f.wait();
    });

    std::cout << "Finished!" << std::endl;
    
    return 0;
}
