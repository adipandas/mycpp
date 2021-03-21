#include <string>
#include <fstream>
#include <iostream>


class Util{
    public:
        static std::string convertToTime(long int input_seconds);
        static std::string getProgressBar(std::string percent);
        static std::ifstream getStream(std::string path);
};


std::string Util::convertToTime(long int input_seconds){
    auto minutes = input_seconds / 60;
    auto hours = minutes / 60;
    auto seconds = int(input_seconds%60);
    minutes = int(minutes%60);
    std::string result = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);
    return result;
}


std::string Util::getProgressBar(std::string percent){
    std::string result = "0% ";
    int _size = 50;
    int boundaries = (std::stof(percent)/ 100) * _size;

    for (int i=0; i < _size; i++){
        if (i <= boundaries){
            result += "|";
        } else {
            result +=" ";
        }
    }
    result+= " " + percent.substr(0, 5) + " /100%\n";

    return result;
}


std::ifstream Util::getStream(std::string path){
    std::ifstream stream(path);
    if (!stream){
        throw std::runtime_error("Non-existing PID");
    }
    return stream;
}


int main(){
    Util u;
    std::cout << u.convertToTime(10000) << "\n";
    
    std::cout << u.getProgressBar("10");
    std::cout << u.getProgressBar("20");
    std::cout << u.getProgressBar("30");
    std::cout << u.getProgressBar("40");
    std::cout << u.getProgressBar("60");
    std::cout << u.getProgressBar("90");
    std::cout << u.getProgressBar("100");
}
