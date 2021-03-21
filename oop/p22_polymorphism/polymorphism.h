#ifndef COMMONS
#define COMMONS

#include <iostream>
#include <string>
#include <cmath>
#include <assert.h>

#endif


#ifndef MY_CONSTANTS
#define MY_CONSTANTS

#define PI 3.14159

#endif


#ifndef POLYMORPHISM_H
#define POLYMORPHISM_H

class Human{
    public:
        std::string name="Jane";
};

class Dog{
    public:
        std::string name="Dog";
};

void Hello();
void Hello(Human);
void Hello(Dog);



// pure abstract class
class Vehicle{
    virtual void Move(double v, double phi) = 0;   // virtual function
};


class ParticleModel: public Vehicle{
    public:
        double x=0, y=0, theta=0;
        void Move(double v, double phi) override;   // overide keyword makes compiler check that signature of virtual function and the function in derived class is same.
};


class BicycleModel: public ParticleModel{
    public:
        void Move(double v, double phi) override;
        double length = 1.0;     // bicycle length
};


//Polygon
class Polygon{
    protected:
        int width__;
        int height__;

    public:
        void SetAttributes(int w, int h);
        virtual int Area() const = 0;
};


class Triangle: public Polygon{
    public:
        Triangle(int w, int h);
        int Area() const override;
};


class Rectangle: public Polygon{
    public:
        Rectangle(int w, int h);
        int Area() const override;
};


// operator overloading example
class Point{
    public:
        int x;
        int y;

        Point(int x, int y);
        Point operator+(const Point &addend);   // operator overloading 
};

#endif
