#include <iostream>
#include <string>


class Car{  // parent class
    public:
        Car(){
            color = "White";
            n = 1;
        }

        Car(std::string color, int n){
            color = color;
            n = n;
        }

        void Talk(){
            std::cout << "I am a Parent Car.\n";
        }

        std::string color;
        int distance = 0;
        int n;
};


class Sedan: public Car{ // child class

    public:
        Sedan(std::string color, int n): Car{color, n}{}

        void Talk(){
            std::cout << "I am Child class. I am a SEDAN.\n";
        }
};


int main(){
    Car car1 = Car();
    Car car2("Orange", 2);
    Sedan car3("Green", 4);

    car1.Talk();
    car2.Talk();
    car3.Talk();
}
