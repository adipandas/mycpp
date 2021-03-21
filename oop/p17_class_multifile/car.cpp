#include <iostream>
#include "car.h"


Car::Car(){
    color = "White";
    number = 0;
}

void Car::Talk(){
    std::cout << "I am PARENT class.\n"; 
}

void Car::IncrementDistance(){
    distance++;
    std::cout << "Distance Increased.\n";
}

void Car::PrintCarData(){
    std::cout << "Car number: " << this->number << "; Car color: " << this->color << "; Car distance: " << distance <<"\n";
}

