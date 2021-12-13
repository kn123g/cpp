#include<iostream>
#include <string>  
#include "std_string.h"
void comparisionMain() {
    char defined_name[] = "karthi";
    std::string name;
        std::cout << "type word 'karthi' "<<std::endl;
        std::cin >> name;
        // compare two character array strcmp if match return 0
        if (std::strcmp(defined_name,name.c_str()) == 0) {
            std::cout << "correctly typed" << std::endl;
        }
        else {
            std::cout << "wrongly typed" << std::endl;
        }
}