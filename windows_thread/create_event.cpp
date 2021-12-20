#include<iostream>
#include<windows.h>

HANDLE thread1;
HANDLE thread2;
HANDLE event;

DWORD thread1_id;
DWORD thread2_id;

DWORD WINAPI ThreadFun1(LPVOID lpParam) {
	//wait for event true state
	WaitForSingleObject(event,INFINITE);
	std::cout << "Thread 1 started" << std::endl;
	return 0;
}

DWORD WINAPI ThreadFun2(LPVOID lpParam) {
	std::cout << "Thread 2 started" << std::endl;
	//signaling event state	to true
	SetEvent(event);
	return 0;
}

void createEventMain() {
	event = CreateEvent(
	NULL, //lpEventAttributes
	FALSE,//bManualReset
	FALSE,//bInitialState
	L"MyEvent" //lpName
	);
	if (event == NULL) {
		std::cout << "\ncouldn't create event" <<std::endl;
	}
	else {
		std::cout << "\ncreated event" << std::endl;
	}
	thread1 = CreateThread(
		NULL, //lpSecurityDescriptor 
		0, //dwStackSize  by default 1MB
		ThreadFun1, //lpStartAddress 
		NULL, //lpParameter
		0, //dwCreationFlags 
		&thread1_id //lpThreadId 
	);
	thread2 = CreateThread(
		NULL, //lpSecurityDescriptor 
		0, //dwStackSize  by default 1MB
		ThreadFun2, //lpStartAddress 
		NULL, //lpParameter
		0, //dwCreationFlags 
		&thread2_id //lpThreadId 
	);
}