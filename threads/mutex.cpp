#include<iostream>;
#include<mutex>;
#include<thread>
#include<vector>
int locked_value = 0;
int normal_value = 0;
std::mutex m;
void inc() {
	for (int i = 0; i < 10000; i++) {
		normal_value++;
	}
	m.lock();
	for (int i = 0; i < 10000; i++) {
		locked_value++;
	}
	m.unlock();
	
}
void mutexMain() {
	std::vector<std::thread> threads;
		// creating thread using lambda expression
		std::thread t1([&]() {
			for (int i = 0; i < 10000; i++) {
				normal_value++;
			}
			// locking critical block of code using mutex
			m.lock();
			for (int i = 0; i < 10000; i++) {
				locked_value++;
			}
			m.unlock();
		});
		// creating thread using function pointer
		for (int i = 0; i < 10; i++) {
			//emplace_back Inserts a new element at the end of the container, right after its current last element
			threads.emplace_back(inc);
		}

		t1.join();
		for (auto& t : threads)
		{
			t.join();
		}
		std::cout << "\n\n normal value : " << normal_value << " locked value : " << locked_value << std::endl;
}