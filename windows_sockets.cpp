#ifdef _WIN32
#include "socket.h"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>//for socket operations
#pragma comment(lib, "ws2_32.lib") //for identify adress

using namespace std;

void initSockets_(){
    WSADATA wsaData;
    int init = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (init < 0) {
        std::cerr << "Init error" << endl;
    }
}

void closeSocket_(int socket){
  closesocket(socket);
}
#endif
