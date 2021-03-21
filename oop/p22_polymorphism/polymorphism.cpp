#include "polymorphism.h"

void Hello(){
    std::cout << "Hello, World!\n";
}


void Hello(Human human){
    std::cout << "Hello, Human!\n";
}

void Hello(Dog Dog){
    std::cout << "Hello, Dog!\n";
}


void ParticleModel::Move(double v, double phi) {
    // v is velocity and phi is delta change in angle.
    this->theta += phi;

    this->x += v * cos(this->theta);
    this->y += v * sin(this->theta);
}


void BicycleModel::Move(double v, double phi) {
    // v is velocity and phi is delta change in angle.

    this->theta += v * tan(phi) / this->length;
    this->x += v * cos(this->theta);
    this->y += v * sin(this->theta);
}


void Polygon::SetAttributes(int w, int h){
    this->width__ = w;
    this->height__ = h;
}


Triangle::Triangle(int w, int h){
    width__ = w;
    height__ = h;
}


int Triangle::Area() const{
    return this->height__*this->width__/2;
}


Rectangle::Rectangle(int w, int h){
    width__ = w;
    height__ = h;
}


int Rectangle::Area() const{
    return this->height__ * this->width__;
}


Point::Point(int x, int y): x(x), y(y){}


Point Point::operator+(const Point &addend){
    Point sum(x, y);
    sum.x += addend.x;
    sum.y += addend.y;
    return sum;
}
