#include<thread>
#include<iostream>
#include<mutex>
#include<queue>

std::mutex pc_mutex;
std::queue<int> q;
std::condition_variable pc_cv;

void producer(int count) {
	while (count) {
		 /*Locks mutex when object is created
		 scope level{} locking, unlock when execution goes out of block
		 explicitly we can to lock,unlock,try_lock
		 if you don't want lock immediately after object creation use defer_lock along with this  
		 cannot be copied but can be moved */
		std::unique_lock<std::mutex> ul(pc_mutex);
		/* releases lock mutex uland wait, if condition return false
		lock mutex ul, if condition return true */
		pc_cv.wait(ul, []() { return q.size() == 0; });
		std::cout << "producing \t"<< count << std::endl;
		q.push(count);
		count--;
		//explicit unlock is optional, automatically unlock after end of scope
		ul.unlock();
		//if there is many consumer we can use notify_all
		pc_cv.notify_one();
	}
}

void consumer() {
	int consume;
	do {
		/*Locks mutex when object is created
		 scope level{} locking, unlock when execution goes out of block
		 explicitly we can to lock,unlock,try_lock
		 if you don't want lock immediately after object creation use defer_lock along with this  
		 cannot be copied but can be moved*/
		std::unique_lock<std::mutex> ul(pc_mutex);
		/* releases lock mutex uland wait, if condition return false
		lock mutex ul, if condition return true */
		pc_cv.wait(ul, []() { return q.size() > 0; });
		consume = q.back();
		std::cout << "consuming \t";
		std::cout << consume << std::endl;
		q.pop();
		//explicit unlock is optional, automatically unlock after end of scope
		ul.unlock();
		pc_cv.notify_one();
	} while (consume);
}

void producerConsumerMain() {
	std::cout << "producer & consumer"<<std::endl;
	std::thread t1(producer,10);
	std::thread t2(consumer);

	t1.join();
	t2.join();
}
