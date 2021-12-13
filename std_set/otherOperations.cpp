#include <iostream>
#include <string>
#include <set>
#include "std_set.h";



void afterOperation(std::set<std::string>& employees) {
	for (std::set<std::string>::iterator employee = employees.begin(); employee != employees.end(); ++employee)
	{
		std::cout << (*employee)<< std::endl;
	}
}

void otherOperationsMain(std::set<std::string>& employees) {

	std::cout << "\nInserting new pair (karthi)";
	// inserting new pair
	employees.insert("karthi");

	std::cout << "\nafter inserting" << std::endl;
	afterOperation(employees);

	std::cout << "\n erasing Dolly";
	std::set<std::string>::iterator it = employees.find("Dolly");
	employees.erase(*it);
	std::cout << "\nafter erasing" << std::endl;
	afterOperation(employees);

	// map size
	std::cout << "set size : " << employees.size() << std::endl;
}