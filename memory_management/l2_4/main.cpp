/*
Row major language
Row operation are faster in C++.
Rows are arranged as consecutive memory blocks.
*/

#include <iostream>
#include <chrono>

int main(){
    const int size = 1000;
    static int x[size][size];

    auto t1_col = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++){
        for (int j = 0; j< size; j++){
            x[j][i] = i+j;    // column first
            // std::cout << &x[j][i] << ": i=" << i <<", j=" << j << std::endl;
        }
    }
    auto t2_col = std::chrono::high_resolution_clock::now();
    auto duration_col = std::chrono::duration_cast<std::chrono::microseconds>(t2_col-t1_col).count();    
    
    auto t1_row = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++){
        for (int j = 0; j< size; j++){            
            x[i][j] = i+j;    // row first -  faster in C++
            // std::cout << &x[i][j] << ": i=" << i <<", j=" << j << std::endl;
        }
    }
    auto t2_row = std::chrono::high_resolution_clock::now();
    auto duration_row = std::chrono::duration_cast<std::chrono::microseconds>(t2_row-t1_row).count();

    std::cout << "Column First Operations: Execution time: " << duration_col << " microseconds" << std::endl;
    std::cout << "   Row First Operations: Execution time: " << duration_row << " microseconds" << std::endl;

    return 0;
}
