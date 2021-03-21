#include <cassert>
#include <iostream>
#include <string>
#include <vector>


class Car{  // parent class
    public:
        Car(){
            color = "White";
            n = 1;
        }

        Car(std::string color, int n){
            color = color;
            n = n;
        }

        void Talk(){
            std::cout << "I am a Parent Car.\n";
        }

        std::string color;
        int distance = 0;
        int n;
};


class Sedan: public Car{ // child class

    public:
        Sedan(std::string color, int n): Car{color, n}{}

        void Talk(){
            std::cout << "I am Child class. I am a SEDAN.\n";
        }
};


class Date {
    public:
        Date(int day, int month, int year);
        
        int Day() const {return day_;}
        void  Day(int day);
        
        int Month() const{return month_;}
        void Month(int month);

        int Year() const {return year_;}
        void Year(int year);

        std::string String() const;
    private:
        bool LeapYear(int year) const;
        int DaysInMonth(int month, int year) const;
        int day_{1};
        int month_{1};
        int year_{0};
};


Date::Date(int day, int month, int year){
    Year(year);
    Month(month);
    Day(day);
}


int Date::DaysInMonth(int month, int year) const {
    if (month==2) {
        return LeapYear(year)? 29 : 28;
    } else if (month == 4 || month == 6 || month==9 || month==11){
        return 30;
    } else {
        return 31;
    }
}


bool Date::LeapYear (int year) const{
    if (year%4 ==0) {

        if (year%100 == 0){

            if (year%400 == 0){
                return true;
            } else {
                return false;
            }

        } else {
            return true;
        }
    } else {
        return false;
    }
}


void Date::Day(int day){
    if (day>=1 && day<=DaysInMonth(Month(), Year())) day_ = day;
}


void Date::Month(int month){
    if (month>=1 && month<=12) month_ = month;
}


void Date::Year(int year){
    year_ = year;
}


std::string Date::String() const{
    std::string date_str;
    std::vector<std::string> months{"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    date_str = months[Month()-1] + " " + std::to_string(Day()) + ", " + std::to_string(Year());
    return date_str;
}


int main(){
    Car car1 = Car();
    Car car2("Orange", 2);
    Sedan car3("Green", 4);
    car1.Talk();
    car2.Talk();
    car3.Talk();

    Date today(15, 3, 2021);
    assert(today.String()=="March 15, 2021");
}
