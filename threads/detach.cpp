
/*DETACH NOTES
0. This is used to detach newly created thread from the parent thread.
1. Always check before detaching a thread that it is joinable otherwise we may end up double detaching and
double detach() will result into program termination.
2. If we have detached thread and main function is returning then the detached thread execution is suspended*/

#include<iostream>;
#include<chrono>;
#include<thread>;

void run1(int x) {
	while (x-- > 0) {
		std::cout << x << std::endl;
	}
}
void detachMain() {
	std::cout << "\n Thread Detach"<<std::endl;
	std::cout << "main thread started" << std::endl;
	std::thread thread(run1, 3);

	thread.detach();
	//using double detach so checking for joinable before join to avoid runtime error
	if (thread.joinable()) {
		thread.detach();
	}
	//std::this_thread::sleep_for(std::chrono::seconds(3));
	std::cout << "ending main thread" << std::endl;
}