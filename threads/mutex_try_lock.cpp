#include<iostream>;
#include<mutex>;

int counter = 0;
std::mutex mu;
void increamentCounter1000Times() {
	for (int i=0; i < 1000;i++) {
		//try_lock tries to lock but if couldn't don't wait
		//execute like non-blocking
		if (mu.try_lock()) {
			counter++;
			mu.unlock();
		}
	}
}

void mutexTryLockMain() {
	std::thread t1(increamentCounter1000Times);
	std::thread t2(increamentCounter1000Times);
	t1.join();
	t2.join();
	std::cout << "counter : "<<counter;
}