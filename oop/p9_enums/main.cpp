/*
How to use Enum
*/

#include <iostream>
#include <string>


enum class State {kObstacle, kEmpty};


// function takes enum and returns a string based on the input enum.
std::string cellString(const State a){
    std::string s;

    switch (a)
    {
    case State::kEmpty:
        s = "0 ";
        break;
    case State::kObstacle:
        s = "⛰️ ";
        break;
    }
    return s;
}


int main(){
    enum class Color {white, black, blue, red, green};      // enum def
    enum class Direction {kUp, kDown, kRight, kLeft};       // enum def

    Color mycolor = Color::red;

    if (mycolor == Color::red){
        std::cout << "Color is red." << "\n";
    } else {
        std::cout << "Color is not red." << "\n";
    }

    Direction d = Direction::kUp;

    switch (d){
        case Direction::kUp: {
            std::cout << "Going UP." << "\n";
            break;
        }
        case Direction::kDown: {
            std::cout << "Going DOWN." << "\n";
            break;
        }
        case Direction::kLeft: {
            std::cout << "Going LEFT." << "\n";
            break;
        }
        case Direction::kRight:{
            std::cout << "Going RIGHT." << "\n";
            break;
        }
    }


    std::cout << cellString(State::kObstacle) << "\n";
    std::cout << cellString(State::kEmpty) << "\n";
}
