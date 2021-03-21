#include "sedan.h"


int main(){
    Car car("Green",9);
    car.Talk();
    car.PrintCarData();

    Sedan sedan("Blue", 10);
    sedan.Talk();
    sedan.PrintCarData();

    Sedan sedan_temp = Sedan();
    sedan_temp.Talk();
    sedan_temp.PrintCarData();
    sedan_temp.IncrementDistance();
    sedan_temp.PrintCarData();
}
