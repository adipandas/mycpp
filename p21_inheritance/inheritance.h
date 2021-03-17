#ifndef COMMONS
#define COMMONS

#include <iostream>
#include <string>
#include <cmath>
#include <assert.h>

#endif


#ifndef INHERITANCE_ONE_H
#define INHERITANCE_ONE_H

// Parent class
class Vehicle{
    public:
        void Print() const;
        int wheels = 0;
        std::string color = "blue";
        int drivewheels = 2;
};


class Car: public Vehicle{
    public:
        bool sunroof = false;
};

class Bicycle: public Vehicle {
    public:
        bool kickStand{true};
};

class Truck: public Vehicle {
    public:
        bool lorry{true};
};

class Sedan: public Car{};

#endif


#ifndef INHERITANCE_TWO_H
#define INHERITANCE_TWO_H

class Animal{
    public:
        std::string color;
        std::string name;
        int age;
};


class Snake: public Animal{
    public:
        float length;
        void MakeSound() const;
};



class Pet{
    public:
        std::string pet_name;
};


class Dog: public Animal, public Pet{
    public:
        std::string breed;
};

class Cat: public Animal, public Pet{
    public:
        std::string color;
        float height;
        void MakeSound() const;
};

#endif


#ifndef INHERITANCE_THREE_H
#define INHERITANCE_THREE_H

class BankAccount{
    public:
        void Number(int number){
            number_ = number;
        }

        int Number() const{
            return number_;
        }

        double Funds() const{
            return funds_;
        }

        void Funds(double funds){
            funds_ = funds;
        }

        std::string Name() const{
            return this->name_;
        }

        void Name(std::string name){
            this->name_ = name;
        }

    private:
        int number_;
        std::string name_;
        double funds_;
};

#endif


#ifndef INHERITANCE_FOUR_H
#define INHERITANCE_FOUR_H

class Square{
    public:
        Square(int s): side_(s){}
    
    private:
        friend class Rectangle;
        int side_{0};
};

class Rectangle{
    public:
        Rectangle(int, int);
        Rectangle(const Square& a);
        
        float Area() const;

    private:
        int length_{0};
        int width_{0};
};

#endif
