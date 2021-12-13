#include <iostream> 
#include<string>
#include "std_string.h";
void conversionMain() {
    std::string s1 = "Hello";
    char ch[] = { 'C', '+', '+' ,'\0'};

    //convert to string from character array string(ch)
    std::string s2 = std::string(ch);

    //convert to const character array from string s2.c_str()
    const char* s3 = s2.c_str();

    ///convert to character array from string s2.c_str()
    char* s4 = _strdup(s2.c_str());
    std::cout << "character : "<< ch << std::endl;
    std::cout << "character to string string(ch) : "<< s2 << std::endl;
    std::cout << "string to const character s2.c_str() : " << s3 << std::endl;
    std::cout << "string to character _strdup(s2.c_str()) : " << s4 << std::endl;
}