/*
In layman's terms:
rvalues - values of right side
lvalues - values of left side

l-value reference can be alternative name for an object

After this : realize that some copy operations can be saved by references to temporary rvalues such as after addition (example below). This can make the code efficient.
*/


#include<iostream>


void myfunc(int &val){
    ++val;
}


int main(){
    int i, j, *p;  // stack variables

    i = 41;   // i is lvalue; 41 is rvalue

    p = new int;  // pointer to int
    *p = i;     // dereference pointer is an lvalue
    delete p;

    ((i < 41)? i: j) = 23; // conditional operator returns an lvalue (either i or j)
    
    //incorrect useage of rvalues and lvalues
    // 42 = i; // error: left operand must be an lvalue
    // j * 41 = 23; // error: left operand must be an lvalue

    int a = 1;      // a is l-value, 1 is r-value
    int &b = a;     // b is a referance to l-value `a`
    ++a;
    ++b; 
    std::cout << "a = " << a << ", b = " << b << std::endl;
    myfunc(a);
    std::cout << "a = " << a << std::endl;

    // myfunc(42);  // rvalue passed as input to function with arg as lvalue reference does not work
    // myfunc(a+b);  // a+b is evaluated and stored in temporary rvalue. rvalue as input to function with args as lvalue reference is error.

    int m = 10;  // m is l-value; 10 is r-value
    int n = 20;   // n is l-value; 20 is r-value
    int o = m+n;   // o is l-value; (m+n) create a temporary rvalue which is then copied to `o` and then temporary rvalue is deleted.
    int &&q = m + n; // &&q is reference to r-value; (m+n) create a temporary r-value after addition.

    std::cout << "o = " << o << ", q = " << q << std::endl;  
}