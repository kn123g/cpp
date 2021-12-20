#include"windows.h"
#include<iostream>
DWORD WINAPI ThreadFun(LPVOID lpParam) {
	std::cout << "\nThread running"<<std::endl;
	return 0;
}
void createThreadMain() {
	HANDLE thread;
	DWORD threadid;
	thread = CreateThread(
		NULL, //lpSecurityDescriptor 
		0, //dwStackSize  by default 1MB
		ThreadFun, //lpStartAddress 
		NULL, //lpParameter
		0, //dwCreationFlags 
		&threadid //lpThreadId 
	);
	if (thread == NULL) {
		std::cout << "Thread Creation Failed & Error No --> " << GetLastError() << std::endl;
	}
	std::cout << "Thread creation success" << std::endl;
	std::cout << "Thread ID --> " << threadid << std::endl;
	CloseHandle(thread);
	std::cout << "Closed thread id " << threadid << std::endl;
}