#ifndef SEDAN_H
#define SEDAN_H

#include "car.h"

class Sedan: public Car{
    public:
        Sedan();
        Sedan(std::string color, int n);
        void Talk();

    private:
        int number;
        std::string color;
        int distance;
};

#endif
