#include<iostream>
#include <map>
#include <string>
std::map<int, std::string> iteratorMain()
{
    std::map<int, std::string> employees;

    employees[101] = "Nikita";
    employees[105] = "John";
    employees[103] = "Dolly";
    employees[104] = "Deep";
    employees[102] = "Aman";
    std::cout << "employees[104]=" << employees[104] << std::endl << std::endl;
    std::cout << "Map size: " << employees.size() << std::endl;
    for (std::map<int, std::string>::iterator employee = employees.begin(); employee != employees.end(); ++employee)
    {
        std::cout << (*employee).first << ": " << (*employee).second << std::endl;
    }
    std::cout << std::endl << "Reverse Order:" << std::endl;
    for (std::map<int, std::string>::reverse_iterator employee = employees.rbegin(); employee != employees.rend(); ++employee)
    {
        std::cout << (*employee).first << ": " << (*employee).second << std::endl;
    }
    return employees;
}