#include<iostream>
#include <set>
#include <string>
std::set<std::string> iteratorMain()
{
    std::set<std::string> employees;  
    employees.insert("Nikita");
    employees.insert("John");
    employees.insert("Dolly");
    employees.insert("Deep");
    employees.insert("Aman");

    std::cout << "List all set"<<std::endl;
    for (std::set<std::string>::iterator employee = employees.begin(); employee != employees.end(); ++employee)
    {
        std::cout << (*employee)<< std::endl;
    }

    std::cout << "find Dolly in set" << std::endl;
    std::set<std::string>::iterator it = employees.find("Dolly");
    if (it == employees.end()) {
        // not found  
        std::cout << "Element not found" << std::endl;
    }
    else {
        // found  
        std::cout << "Iterator points to " << *it << std::endl;
    }

    std::cout << std::endl << "List all set in Reverse Order:" << std::endl;
    for (std::set<std::string>::reverse_iterator employee = employees.rbegin(); employee != employees.rend(); ++employee)
    {
        std::cout << (*employee)<< std::endl;
    }
    return employees;
}