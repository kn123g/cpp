#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>

int countincreaseFor = 0;
int countincreaseUntil = 0;
// timed mutex
std::timed_mutex timed_mutex_for;
std::timed_mutex timed_mutex_until;
void increaseFor() {
	//try_lock_for takes time in seconds
	//try_lock_for waits for given time and lock 
	//lock immediately when it is free to lock
	if(timed_mutex_for.try_lock_for(std::chrono::seconds(2))) {
		std::cout << "entered lock and increasing"<<std::endl;
		countincreaseFor++;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		timed_mutex_for.unlock();
	}
	else {
		std::cout << "couldn't enter lock" << std::endl;
	}
}

void increaseUntil() {
	auto now = std::chrono::steady_clock::now();
	//try_lock_untill takes clock time
	//try_lock_untill waits for given time and lock 
	//lock immediately when it is free to lock
	if (timed_mutex_until.try_lock_until(now + std::chrono::seconds(2))) {
		std::cout << "entered lock and increasing" << std::endl;
		countincreaseUntil++;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		timed_mutex_until.unlock();
	}
	else {
		std::cout << "couldn't enter lock" << std::endl;
	}
}
void timedMutexMain() {
	std::cout << "timed mutex try_lock_for" << std::endl;
	std::thread t1(increaseFor);
	std::thread t2(increaseFor);
	t1.join();
	t2.join();
	std::cout << "\ntimed mutex try_lock_until" << std::endl;
	std::thread t3(increaseFor);
	std::thread t4(increaseFor);
	t3.join();
	t4.join();
}