#include "pch.h"
#include "framework.h"
#include<iostream>

int __declspec(dllexport) calculate(int action) {
	int a, b;
	std::cout << "Enter A\t";
	std::cin >> a;
	std::cout << "Enter B\t";
	std::cin >> b;
	switch (action) {
	case 1:
		return a + b;
		break;
	case 2:
		return a - b;
		break;
	case 3:
		return a * b;
		break;
	case 4:
		return a / b;
		break;
	default:
		std::cout << "Couldn't able to perform action\n";
		return 0;
		break;
	}
}