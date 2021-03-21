#include "sedan.h"
#include <iostream>


Sedan::Sedan(){
    number = 0;
    color = "White";
}


Sedan::Sedan(std::string color, int n): Car(color, n){
    std::cout << "In other constructor where Car parent is initialized.\n";
    this->number = n;
    this->color = color;
}


void Sedan::Talk(){
    std::cout << "I am a chile class.\n";
}
