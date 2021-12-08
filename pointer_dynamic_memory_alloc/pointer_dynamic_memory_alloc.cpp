#include<iostream>

int main() {
    int static_array[5];
    int size = 5;
    int* dynamic_array = new int[size];
    *static_array = 9;
    *dynamic_array = 10;
    std::cout << *static_array;
    std::cout << "\n";
    std::cout << *dynamic_array;

}