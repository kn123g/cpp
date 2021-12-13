#include <iostream>  
#include <string>
void concatMain()
{
    std::string str[2];
    std::cout << "Enter the string 1 : ";
    std::cin>>str[0];
    std::cout << "Enter the string 2 : ";
    std::cin >> str[1];
    // concat two strings
    std::string concat_str = str[0] + str[1];
    std::cout << "concatenated string : " << concat_str;
}