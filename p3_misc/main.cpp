/*
- Declare int
- Declare string
- Declare vector - 3 ways to do it
- Declare variable using `auto` keyword
- Interate over vector
- Access size of vector - vector.size()
- For loops
- If statement
- Increament operator: post increment and pre-increment
- Post increment: i++ :: assign and then increase value
- Pre increment: ++i :: increment and then assign value
- Decrement operator: post decrement and pre-decrement
- const: Promise not to modify the variable.
- constexpr: Guarantee of variable being evaluated at compile time
- pointer:
*/

#include <iostream>
#include <string>
#include <vector>

int main(){
    int a = 9;

    const auto PI = 3.14;    // my value of pi - const value cannot be changed.
    constexpr auto max_angle = 2*3.14;  // Max. value of angle depends on the value of variable PI. Evaluated at compile time and cannot be changed after that.
    
    std::cout<< a <<"\n";

    std::string b;  // declare a string variable
    b = "Hello, World!";    // assign value to string var.

    std::cout << b << "\n";

    std::vector<int> c;             // declaring vector of int
    c = {1, 2, 3};                  // initializing the vector of ints

    std::vector<int> c2{1,2,3,4};     //another method to declare and initailize vector
    std::vector<int>c3 = {1,2,3,4};     // yet another method to declare and initialize vector

    for (int i=0; i<c3.size(); i++){      // for loop
        std::cout<< c3[i]<< " ";
    }
    std::cout<< "\n";

    for (int _a : c){
        std::cout<< _a << "\n";
    }


    std::vector<std::string> d;     // declaring vector of string
    d = {"A", "for", "Apple"};      // initializing the vetor of strings

    for (std::string _s : d){
        std::cout<<_s<<"\n";
    }

    std::vector<std::vector<int>> vec2d;        // 2D vector
    vec2d = {{1, 2, 3},{4, 5, 6}};

    for (std::vector<int> _v : vec2d){          // iterate over 2D vector
        for (int _c : _v){
            std::cout<<_c<<" ";
        }
        std::cout<<"\n";
    }

    std::cout<<"\nUse auto keyword:"<<"\n";
    for (auto _v:vec2d){                        // use auto keyword
        for (auto _i: _v){
            std::cout << _i << " ";
        }
        std::cout<<"\n";
    }

    std::vector<std::vector<int>> grid;         // store grid in vector
    grid = {{0, 1, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0}};
    
    std::cout<< "\nGrid:"<<"\n";
    for (std::vector<int> row: grid){
        for (int col: row){
            std::cout<<col<<" ";
        }
        std::cout<<"\n";
    }
    std::cout << "Size of grid (or number of rows in grid): " << grid.size() <<"\n";
    std::cout << "Size of each row in grid (or number of columns in grid): " << grid[0].size() << "\n";

    std::cout<<"Post increment operator i++ and Pre increment operator ++i"<<"\n";
    int i = 1;
    std::cout<<"starting i:"<< i <<"\n";
    int l = i++;
    int m = ++i;
    std::cout<<"final i:"<< i <<"\n";
    std::cout<<"l:"<< l <<"\n";
    std::cout<<"m:"<< m <<"\n";

    std::cout<<"Post decrement operator i-- and Pre decrement operator --i"<<"\n";
    i = 10;
    std::cout<<"starting i:"<< i <<"\n";
    l = i--;
    m = --i;
    std::cout<<"final i:"<< i <<"\n";
    std::cout<<"l:"<< l <<"\n";
    std::cout<<"m:"<< m <<"\n";

    bool my_bol  = true;
    if (my_bol){
        std::cout<<"In If statement!!"<<"\n";
    } else {
        std::cout<<"In Else statement!!" << "\n";
    }

    my_bol  = false;
    if (my_bol){
        std::cout<<"In If statement!!"<<"\n";
    } else {
        std::cout<<"In Else statement!!" << "\n";
    }
    
    int my_while_var = 0;
    while (my_while_var < 10){
        std::cout << my_while_var << " ";
        my_while_var++;
    }
    std::cout<<"\n";


    // pointer
    int xx = 5;
    int * ptr_xx = &xx;
    std::cout << "value of xx: " << xx <<"\n";
    std::cout << "Address of xx: " << &xx << "\n";
    std::cout << "ptr_xx: " << ptr_xx << "\n";
    std::cout << "Value of ptr_xx: " << *ptr_xx << "\n";

    xx = 8;
    std::cout << "New xx: " << xx << "\n";
    std::cout << "Address of xx: " << &xx << "\n";
    std::cout << "ptr_xx: " << ptr_xx << "\n";
    std::cout << "Value of ptr_xx: " << *ptr_xx << "\n"; 

    *ptr_xx = 10;
    std::cout << "New xx: " << xx << "\n";
    std::cout << "Address of xx: " << &xx << "\n";
    std::cout << "ptr_xx: " << ptr_xx << "\n";
    std::cout << "Value of ptr_xx: " << *ptr_xx << "\n"; 

    // pointer to vectors/objects
    std::vector<int> vec{1,2,3,4,5};
    std::vector<int> * ptr_vec = &vec;
    std::cout<<"Original vector: ";
    for (auto v: vec){
        std::cout<<v<<" ";
    }
    std::cout << "\n";
    std::cout << "First element of the vector using pointer:" << (*ptr_vec)[0] << "\n";
    
}
