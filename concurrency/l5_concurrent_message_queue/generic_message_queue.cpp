/*
* Template class of Message Queue
* A message queue is an effective and very useful mechanism to enable a safe and reusable communication channel between threads.
* build using: g++ generic_message_queue.cpp -pthread
*/


#include <iostream>
#include <thread>
#include <future>
#include <algorithm>
#include <queue>
#include <mutex>


template<class T>
class MessageQueue{
    private:
        std::deque<T> _messages;
        std::mutex _mtx;
        std::condition_variable _cond;
    
    public:
        MessageQueue(){}  // constructor

        T receieve(){ // receive return from queue
            std::unique_lock<std::mutex> ul(_mtx);
            _cond.wait(ul, [this](){return !_messages.empty();});

            T msg = std::move(_messages.back());
            _messages.pop_back();

            return msg;
        }

        void send(T &&msg){   // send data to queue
            std::lock_guard<std::mutex> lg(_mtx);
            // std::cout << "  Message " << msg << " has been sent to queue" << std::endl;  // uncomment this line to see output on console
            _messages.emplace_back(std::move(msg));
            _cond.notify_one();
        }
};




int main(){
    std::shared_ptr<MessageQueue<int>> queue(new MessageQueue<int>);

    std::cout << "Spawning threads... " << std::endl;
    std::vector<std::future<void>> futures;
    for (int i=0; i<100; ++i){
        futures.emplace_back(std::async(std::launch::async, &MessageQueue<int>::send, queue, i));
    }

    while(true){
        int m = queue->receieve();
        std::cout << "recieved #" << m << std::endl; 
    }

    std::for_each(futures.begin(), futures.end(), [](std::future<void> &f){f.wait();});

    return 0;
}
