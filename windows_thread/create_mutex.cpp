#include<iostream>
#include<windows.h>

int count = 0;
HANDLE hmutex;

HANDLE even_thread;
DWORD even_threadid;

HANDLE odd_thread;
DWORD odd_threadid;

DWORD WINAPI evenPrint(LPVOID lpParam) {
	while(count<10){
		//locks hmutex
		WaitForSingleObject(hmutex, INFINITE);
		if (count % 2 == 0) {
			std::cout << "Even " << count++ << std::endl;
		}
		//releases hmutex
		ReleaseMutex(hmutex);
	}		
	
	return 0;
}
DWORD WINAPI oddPrint(LPVOID lpParam) {
	while (count < 10) {
		//locks hmutex
		WaitForSingleObject(hmutex, INFINITE);
		if (count % 2 != 0) {
			std::cout << "Odd " << count++ << std::endl;
		}
		//releases hmutex
		ReleaseMutex(hmutex);
	}

	return 0;
}

void mutexMain() {
	hmutex = CreateMutex(
		NULL,
		FALSE,
		NULL
	);
	even_thread = CreateThread(
		NULL, //lpSecurityDescriptor 
		0, //dwStackSize  by default 1MB
		evenPrint, //lpStartAddress 
		NULL, //lpParameter
		0, //dwCreationFlags 
		&even_threadid //lpThreadId 
	);
	odd_thread = CreateThread(
		NULL, //lpSecurityDescriptor 
		0, //dwStackSize  by default 1MB
		oddPrint, //lpStartAddress 
		NULL, //lpParameter
		0, //dwCreationFlags 
		&odd_threadid //lpThreadId 
	);
	std::cout << "\nmutex programs" <<std::endl;
}