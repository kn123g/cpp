#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>

std::mutex m1;
std::mutex m2;

void run1() {
	m1.lock();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	//here m2 is locked in run2 so it will be keep on waiting
	m2.lock();
	std::cout << "Run1 Executing"<<std::endl;
	m1.unlock();
	m2.unlock();
}

void run2() {
	m2.lock();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	//here m1 is locked in run2 so it will be keep on waiting
	m1.lock();
	std::cout << "Run2 Executing" << std::endl;
	m2.unlock();
	m1.unlock();
}

void correctRun1() {
	//here order is same in Run1 and Run2 first m1 is locked and then m2
	m1.lock();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	m2.lock();
	std::cout << "correct Run1 Executing" << std::endl;
	m1.unlock();
	m2.unlock();
}

void correctRun2() {
	//here order is same in Run1 and Run2 first m1 is locked and then m2
	m1.lock();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	m2.lock();
	std::cout << "correct Run2 Executing" << std::endl;
	m1.unlock();
	m2.unlock();
}

void deadLockMain() {

	//here order of locking mutex in both thread is same so there won't be deadlock
	std::thread t3(correctRun1);
	std::thread t4(correctRun2);

	t3.join();
	t4.join();

	std::cout << "Executing deadlock"<<std::endl;
	std::thread t1(run1);
	std::thread t2(run2);
	// here deal lock comes 
	// to avoid deadlock maintain same order for locking mutex in both threads
	t1.join();
	t2.join();

}