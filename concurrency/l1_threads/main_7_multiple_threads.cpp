/*
Fork thread parallelism
*/


#include <iostream>
#include <vector>
#include <thread>


void printHello(){
    std::cout << "Hello from Worker Thread #" << std::this_thread::get_id() << std::endl;
}


int main(){
    std::vector<std::thread> threads;


    // observe interleaving of the console output
    for (size_t i=0; i<10; ++i){

        // Copying thread object (in vector using push_back) causes compiler error
        /*
        std::thread t(printHello);
        threads.push_back(t);
        */

       // moving thread objects will work
       threads.emplace_back(std::thread(printHello));
    }

    std::cout << "Hello from Main thread #" << std::this_thread::get_id() << std::endl;

    for (auto &t: threads){
        t.join();
    }


    // Avoid interleaving by using some delay in per thread for computation.
    std::vector<std::thread> threads_2;
    for (size_t j=0; j<10; ++j){
        threads_2.emplace_back(
            [j](){
                // std::cout << j << std::endl;
                std::this_thread::sleep_for( std::chrono::milliseconds(10*j) );

                std::cout << "Hello from Delayed Worker Thread #" << j << "; thread_id = " << std::this_thread::get_id() << std::endl;
            }
        );

        // Passing the value of j as a reference to the lamda function will result in a bug
        // threads_2.emplace_back(
        //     [&j](){
        //         // std::cout << j << std::endl;
        //         std::this_thread::sleep_for( std::chrono::milliseconds(10*j) );

        //         std::cout << "Hello from Delayed Worker Thread #" << j << "; thread_id = " << std::this_thread::get_id() << std::endl;
        //     }
        // );
    }

    std::cout << "Hello 2 from Main thread." << std::endl;

    for (auto &t : threads_2){
        t.join();
    }

}
