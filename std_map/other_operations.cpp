#include <iostream>
#include <string>
#include <map>
#include "std_map.h";



void afterOperation(std::map<int, std::string> &employees) {
	for (std::map<int, std::string>::iterator employee = employees.begin(); employee != employees.end(); ++employee)
	{
		std::cout << (*employee).first << ": " << (*employee).second << std::endl;
	}
}

void otherOperationsMain(std::map<int,std::string>& employees) {

	std::cout << "\nget using key at(104) : ";
	// get values by key
	std::cout<<employees.at(104)<<std::endl;

	std::cout << "\nInserting new pair (109,ganesh)";
	// inserting new pair
	employees.insert(std::pair<int, std::string>(109, "ganesh"));

	std::cout << "\nafter inserting"<<std::endl;
	afterOperation(employees);

	std::cout << "\n erasing pair of key 104";
	employees.erase(104);
	std::cout << "\nafter erasing" << std::endl;
	afterOperation(employees);


	std::cout << "find(109) return iterator pointer"<<std::endl;
	//find() returns iterator
	std::map<int, std::string>::iterator it = employees.find(109);
	std::cout << "Iterator points to " << std::endl;
	std::cout << (*it).first << " : " << it->second << std::endl;

	// map size
	std::cout << "\nmap size : " << employees.size() <<std::endl;
}