/*
malloc allocation does not call constructor of class. Returns a void pointer.
type *ptr = malloc(sizeof(type)); 
* use ``free(ptr)`` to free the allocated memory.

* `new` operator allocation calls constructor of the class.
* `delete` operator to deallocate the memory.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>


class MyClass{
    public:
        MyClass();
        ~MyClass();
        void Number(int i);
        int Number();
    
    private:
        int * _number;
};


MyClass::MyClass(){
    std::cout << "Allocate Memory.\n";
    _number = (int *) malloc(sizeof(int));
}


MyClass::~MyClass(){
    std::cout << "Delete Memory.\n";
    free(_number);
}


void MyClass::Number(int i){
    std::cout << "Number Setter called.\n";
    *_number = i;
}


int MyClass::Number(){
    std::cout << "Number getter called.\n";
    return *_number;
}



class MemoryAllocationViz{
    double _number;

    public:
        MemoryAllocationViz(){
            std::cout << "Inside the Class to check memory allocation sequence.\n";
            std::cout << "Constructor called.\n";
        }

        ~MemoryAllocationViz(){
            std::cout << "Destructor called.\n";
        }

        void *operator new(size_t size){
            std::cout << "new: Allocating " << size << "bytes of memory" << std::endl;
            void *p = malloc(size);
            return p;
        }

        void operator delete(void *p){
            std::cout << "delete: Memory is freed again.\n";
            free(p);
        }
};

int main(){
    int i, n;
    char * buffer;

    printf("Enter number of characters in string:");
    scanf("%d", &i);

    buffer = (char *)  malloc(i+1);
    if (buffer == NULL) exit (1);
    
    for (n=0; n<i; n++){
        buffer[n] = rand()%26 + 'a';
    }
    buffer[i]='\0';   // (i+1)th element of string is assigned

    printf("Random string: %s\n", buffer);
    free(buffer);

    /* Allocate memory using malloc (use one of the two given below (one is commented))  */
    // MyClass *mc = (MyClass *) malloc(sizeof(MyClass));   // MyClass *mc = (MyClass *) malloc(sizeof(mc));
    // mc->Number(10);      // EXC_BAD_ACCESS
    // free(mc);

    MyClass *mc = new MyClass();
    mc->Number(8);
    std::cout << mc->Number() <<'\n';
    delete mc;

    // Sequence of allocation and deallocation of memory with new and delete operators.
    std::cout<<"\n\n\n";
    MemoryAllocationViz * mav = new MemoryAllocationViz();
    delete mav;
}
