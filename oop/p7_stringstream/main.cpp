/*
 - sstream - usinging  istringstream to read the input string stream (line from a file.)
 - Understand the behavior of istringstream for string "0,1,2,3,4,5"
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


int main(){
    std::string filepath = "./grid.world";
    
    std::ifstream my_file;
    my_file.open(filepath);

    if (my_file){
        std::string fileline;
        std::string s;

        while (std::getline(my_file, fileline)){
            std::istringstream my_string_stream(fileline);
            
            while (my_string_stream >> s) {
                std::cout << "Success: " << s << "\n";
            }
            std::cout << "Reached end of current line! Reading next line if available..." << "\n";
        }
    }

    std::string number_string("1 2 3 4");
    int n;
    std::istringstream iss(number_string);
    std::cout << "\nReading string with istringstream:"<<std::endl;
    while (iss>>n){
        std::cout << n << " ";
    }
    std::cout << "\n";

    std::string mixed_string("1,2,3,4,5");
    std::cout << "\nReading complex string:" << std::endl;
    std::istringstream iss_mixed(mixed_string);
    int m;
    char c;
    while (iss_mixed >> m >> c){
        std::cout << m << " " << c << " ";  // NOTE: in the string "5" will not print since it will try to extract a number + char. This string does not have any char after 5. 
    }
    std::cout << "\n";
}
