#ifndef CAR_H
#define CAR_H
#include <string>

class Car{
    public:
        Car();
        Car(std::string color, int n): color(color), number(n){}

        void Talk();
        void PrintCarData();
        void IncrementDistance();

    private:
        std::string color;
        int distance = 0;
        int number;
};

#endif
