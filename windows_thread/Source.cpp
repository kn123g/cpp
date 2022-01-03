#include"windows_thread.h"
#include<iostream>
#include<windows.h>
void main() {
	/*createThreadMain();
	Sleep(2000);
	mutexMain();
	Sleep(3000);
	createEventMain();*/
	multipleProducerConsumerMain();
	std::cin.get();
}