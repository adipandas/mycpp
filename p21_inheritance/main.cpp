/*
- Inheritance
- Multi class inheritance
- Privacy in inheritance (also read online.)
- Friend class in inheritance and friend function in inheritance.
*/


#include "inheritance.h"


int main(){
    Car car;
    car.wheels = 4;
    car.color = "Black";
    car.sunroof = true;
    car.drivewheels = 2;

    car.Print();

    if (car.sunroof){
        std::cout << "And a sunroof!\n";
    }
    std::cout<< "The car is " << car.drivewheels << " wheel drive.\n";

    Truck truck;
    if (truck.lorry){
        std::cout << "It is a lorry!\n";
    }
    truck.wheels = 8;
    truck.Print();

    Snake snake;
    snake.length = 2.1;
    snake.MakeSound();
    snake.name = "Snaker";
    snake.color = "Black";

    Cat cat;
    cat.height = 4.5;
    cat.MakeSound();
    cat.color = "White";
    cat.name = "Cat";
    std::cout << cat.color << "\n" << cat.name << "\n";

    Square square(4);
    Rectangle rectangle(square);
    assert(rectangle.Area()==16);
}

