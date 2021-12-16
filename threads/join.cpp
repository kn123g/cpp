/*JOIN NOTES
0. Once a thread is started we wait for this thread to finish by calling join() function on thread object.
1. Double join will result into program termination.
2. If needed we should check thread is joinable before joining. (using joinable() function)


NOTES:
Either join() or detach() should be called on thread object, otherwise during thread object�s destructor it will
terminate the program.Because inside destructor it checks if thread is still joinable ? if yes then it terminates the program*/

#include<iostream>;
#include<chrono>;
#include<thread>;

void run(int x) {
	while (x-- > 0) {
		std::cout << x << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}
void joinMain() {
	std::cout << "\n Thread Join" << std::endl;
	std::cout << "\nmain thread started" << std::endl;
	std::thread thread(run, 3);

	thread.join();
	//using double join so checking for joinable before join to avoid runtime error
	if (thread.joinable()) {
		thread.join();
	}

	std::cout << "ending main thread" << std::endl;
}