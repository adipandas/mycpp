/*
Example of C++ structures
- How to use struct
- Use of <cassert> lib
*/

#include <iostream>
#include <cassert>
#include <string>


struct Date {       // define a simple structure
    int day{1};
    int month{1};
    int year{1};
};


struct MyInfo{
    std::string name;
    std::string lastname;
    std::string where;
    Date date;
};


struct Chupakabra
{
    public:
        void Name(std::string n){name=n;}
        std::string Name(){return name;}
        
        bool IsGrim(){return isGrim;}
        void IsGrim(bool flag){isGrim=flag;}

        std::string Status(){
            if (status){
                return "alive";
            } else {
                return "dead";
            }
        }

        void Status(std::string s){
            if (s == "alive"){
                status = 1;
            } else if (s == "dead"){
                status = 0;
            }
        }

    private:
        std::string name{"JaneDoe"};
        bool isGrim = false;
        int status = 1;     // alive is 1 and dead is zero
};


int main(){
    Date date;
    MyInfo adipandas;
    date.day = 29;
    date.month = 2;
    date.year = 2000;
    assert(date.day == 29);
    assert(date.month == 2);
    assert(date.year == 2000);
    std::cout << "Input date as month/day/year: " << date.month << "/" << date.day << "/" << date.year << "\n";
    adipandas.name = "adipandas";
    adipandas.lastname = "adipandas";
    adipandas.where = "GitHub";
    adipandas.date.day = 11;
    adipandas.date.month = 3;
    adipandas.date.year = 2021;
    assert(adipandas.date.day == 11);
    assert(adipandas.date.month == 3);
    assert(adipandas.date.year == 2021);
    std::cout << "My information given as input:\n";
    std::cout << "Name: " << adipandas.name << std::endl;
    std::cout << "Lastname: " << adipandas.lastname << std::endl;
    std::cout << "Where is " << adipandas.name << ": " << adipandas.where << std::endl;
    std::cout << "My information date in month/day/year: " << adipandas.date.month << "/" << adipandas.date.day <<  "/" << adipandas.date.year << std::endl;
    Chupakabra mac;
    mac.Name("Mac");
    mac.IsGrim(false);
    mac.Status("Alive");
    std::cout << "Chupakabra Name: "<< mac.Name() << "\n";
    if (mac.IsGrim()){
        std::cout << mac.Name() << " is a Grim." << std::endl;
    } else {
        std::cout << mac.Name() << " is not a Grim." << std::endl;
    }
    std::cout << mac.Name() << " is " << mac.Status() << ".\n";
}
