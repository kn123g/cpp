#include<windows.h>
#include<iostream>

CRITICAL_SECTION cs;
CONDITION_VARIABLE cv;
int buffer = 0;
int max_items[20];

DWORD WINAPI ProducerThread(LPVOID lpvoid) {
	for (int i = 0; i < 10; i++) {
		EnterCriticalSection(&cs);
		while (buffer == 5) {
			SleepConditionVariableCS(&cv, &cs, INFINITE);
		}
		buffer++;
		std::cout << "Producer = " << buffer << std::endl;
		Sleep(1000);
		LeaveCriticalSection(&cs);
		WakeConditionVariable(&cv);
	}
	return 0;

}


DWORD WINAPI ConsumerThread(LPVOID lpvoid) {
	for (int i = 0; i < 10;i++) {
		EnterCriticalSection(&cs);
		while (buffer == 0) {
			SleepConditionVariableCS(&cv, &cs, INFINITE);
		}
		std::cout << "Consumer = " << buffer << std::endl;
		buffer--;
		WakeConditionVariable(&cv);
		LeaveCriticalSection(&cs);
	}
	return 0;
}


void multipleProducerConsumerMain() {
	//Handle for thread
	HANDLE hProducer, hConsumer;
	//Initialize Critical Section
	InitializeCriticalSection(&cs);

	//Initialize Conditional Variable
	InitializeConditionVariable(&cv);

	//Create Producer and Consumer thread
	hProducer = CreateThread(
		NULL,
		0,
		&ProducerThread,
		NULL,
		0,
		0);

	hConsumer = CreateThread(
		NULL,
		0,
		&ConsumerThread,
		NULL,
		0,
		0);

	// Wake All Conditional Variable
	WakeAllConditionVariable(&cv);
	// Wait for Single Objects for Thread
	WaitForSingleObject(hProducer, INFINITE);
	WaitForSingleObject(hConsumer, INFINITE);
	system("PAUSE");
}