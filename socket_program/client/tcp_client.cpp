#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include<iostream>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

WSADATA wsaData;
SOCKET ConnectSocket = INVALID_SOCKET;

struct addrinfo* result = NULL,
    * ptr = NULL,
    hints;
char sendbuf[DEFAULT_BUFLEN];
char recvbuf[DEFAULT_BUFLEN];

int iResult;
int recvbuflen = DEFAULT_BUFLEN;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE send_thread;
DWORD WINAPI ThreadFun(LPVOID lpParam) {
    do {
        //sendbuf = NULL;
        //std::cout << "send message ";
        std::cin>>sendbuf;
        //std::cout <<"sending"<<sendbuf<< std::endl;
        if (sendbuf != NULL && sendbuf != "0") {
            //send data
            //std::cout << "sending message :" << sendbuf << std::endl;
            iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
            if (iResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ConnectSocket);
                WSACleanup();
                return 1;
            }
            //printf("Bytes Sent: %ld\n", iResult);
        }
        
    } while (sendbuf != "0");
    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}
void sendThread() {
    DWORD threadid;
    send_thread = CreateThread(
        NULL, //lpSecurityDescriptor 
        0, //dwStackSize  by default 1MB
        ThreadFun, //lpStartAddress 
        NULL, //lpParameter
        0, //dwCreationFlags 
        &threadid //lpThreadId 
    );
    if (send_thread == NULL) {
        std::cout << "Thread Creation Failed & Error No --> " << GetLastError() << std::endl;
    }
}
int __cdecl tcpClient(int argc, char** argv)
{
    // Validate the parameters
    // need to pass server ip or hostname
    if (argc != 2) {
        printf("usage: %s server-name\n", argv[0]);
        return 1;
    }

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }
        /*//newly added
        iResult = getaddrinfo(NULL, argv[1], &hints, &result);
        if (iResult != 0) {
            printf("getaddrinfo failed with error: %d\n", iResult);
            WSACleanup();
            return 1;
        }
        // Setup the TCP port for client socket
        iResult = bind(ConnectSocket, result->ai_addr, (int)result->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            printf("bind failed with error: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            closesocket(ConnectSocket);
            WSACleanup();
            return 1;
        }

        freeaddrinfo(result);
        //newly added */

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }
    else {
        std::cout << "connected to server" << std::endl;
    }

    sendThread();
    // Receive until the peer closes the connection
    do {
        //memset place the given char in each index places of char array
        //arg 0 is used to clear the char array
        memset(recvbuf, 0, recvbuflen);
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            //printf("Bytes received: %d\n", iResult);
            //std::cout << "\033[31m" << recvbuf << "\033[0m" << std::endl;
            SetConsoleTextAttribute(hConsole, 10);
            std::cout << recvbuf << std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while (iResult > 0);

    CloseHandle(send_thread);
    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}