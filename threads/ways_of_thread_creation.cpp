#include <iostream>
#include <thread>

//1) function pointer method
void pointer_run(int x) {
	while (x-- > 0) {
		std::cout << x;
	}
}

// 2) lamda function method
auto lamda_run = [](int x) {
	while (x-- > 0) {
		std::cout << x;
	}
};

// 3) functor or function object method
class Base1 {
public : void operator() (int x) {
		while (x-- > 0) {
			std::cout << x;
		}
	}
};

// 4) non static member function method
class Base2 {
public: void run(int x) {
	while (x-- > 0) {
		std::cout << x;
	}
}
};

// 5) static member function method
class Base3 {
public: static void run(int x) {
	while (x-- > 0) {
		std::cout << x;
	}
}
};



void waysOfThreadCreationMain() {

	std::cout << "\ntypes of thread creation";
	std::cout << "\n function pointer thread : ";
	std::thread pointer(pointer_run,9);
	pointer.join();

	std::cout << "\n lamda thread : ";
	std::thread lamda(pointer_run, 9);
	lamda.join();

	std::cout << "\n function object thread : ";
	std::thread function_object(Base1(), 9);
	function_object.join();

	std::cout << "\n non static data member thread : ";
	Base2 obj;
	std::thread non_static_member_fun(&Base2::run,obj, 9);
	non_static_member_fun.join();

	std::cout << "\n static data member thread : ";
	std::thread static_member_fun(&Base3::run, 9);
	static_member_fun.join();
}
