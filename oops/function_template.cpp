#include<iostream>

template<typename T>

//dynamic code will be created based on type of value received
void show(T value) {
	std::cout << value << '\t';
}

void templateMain() {
	//specifying predefined datatype is optional
	std::cout << "template output\n";
	show(1);
	show("ONE");
	show(1.22f);

	std::cout << '\n';

	show<int>(1);
	show<std::string>("ONE");
	show<float>(1.22f);
	std::cout << '\n';
}