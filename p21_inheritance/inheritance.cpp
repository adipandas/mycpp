#include "inheritance.h"


void Vehicle::Print() const{
    std::cout << "This " << color << " vehicle has " << wheels << " wheels!\n";
}


void Snake::MakeSound() const{
    std::cout << "Hiss!\n";
}

void Cat::MakeSound() const{
    std::cout << "Meow!\n";
}


Rectangle::Rectangle(int length, int width): length_(length), width_(width){}
Rectangle::Rectangle(const Square &a): length_(a.side_), width_(a.side_){}   // using a friend class allows access to private members of friend

float Rectangle::Area() const{
    return this->length_*this->width_;
}