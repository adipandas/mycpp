#include <stdio.h>


void MyFunc(int k){
    printf("%d: %p \n", k, &k);
}

int main(){
    int i = 1;
    printf("%d: %p \n", i, &i);

    int j = 2;
    printf("%d: %p \n", j, &j);

    MyFunc(3);   // k = 3

    int l = 4;
    printf("%d: %p \n", l, &l);

}