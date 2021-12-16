/*NOTES:
1. Condition variables allow us to synchronize threads via notifications.
a.notify_one();
b.notify_all();
2. You need mutex to use condition variable
3. Condition variable is used to synchronize two or more threads.
4. Best use case of condition variable is Producer / Consumer problem.
5. Condition variables can be used for two purposes :
a.Notify other threads
b.Wait for some condition*/
#include<iostream>
#include<thread>
#include<mutex>

int balance = 0;
std::mutex mutex;
std::condition_variable cv;
void addMoney(int money){
	/*
	Locks mutex when object is created
	scope level {} locking, unlock when execution goes out of block
	explicitly cannot unlock lock_guard
	can not copy lock_guard.
	*/
	std::lock_guard<std::mutex> lg(mutex);
	balance = balance + money;
	std::cout << "added money : "<< money << std::endl;
	//notify all waiting condition variable
	cv.notify_all();
	//use when needs to notify to only one thread
	//cv.notify_one();
}
void withdrawMoney(int money){
	// Locks mutex when object is created
	// scope level{} locking, unlock when execution goes out of block
	// explicitly we can to lock,unlock,try_lock
	// if you don't want lock immediately after object creation use defer_lock along with this  
	// cannot be copied but can be moved
	std::unique_lock<std::mutex> ul(mutex);
	// releases lock mutex m and wait, if condition return false
	// lock mutex m, if condition return true
	cv.wait(ul, [] {return (balance != 0) ? true : false; });
	if (balance != 0) {

		if (balance > money) {
			balance = balance - money;
			std::cout << money <<" Money withdrawn" << std::endl;
		}
		else {
			std::cout << "Insufficient balance" <<std::endl;
		}
	}
	
}

void conditionVariableMain() {

	std::thread t1(withdrawMoney, 1000);
	std::thread t2(withdrawMoney, 400);
	std::thread t3(addMoney,500);
	t1.join();
	t2.join();
	t3.join();
}