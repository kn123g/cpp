#include <iostream>;
//#include "../calculate_static/calculate.h";
#include "calculate.h";

int main()
{
	int action = 0;
	do {
		std::cout << "select any one action or 0 to exit \n1.add\n2.substract\n3.multiply\n4.division\n";
		std::cin >> action;
		if (action > 0 && action <= 4) {
			std::cout << "result\t" << calculate(action) << '\n';
		}
		else {
			std::cout << "select valid action\n";
		}

	} while (action != 0);
}
