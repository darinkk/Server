
#include "server_windows.h"
#include <iostream>
#pragma comment(lib, "ws2_32.lib") //for identify adress

using namespace std;

void ServerWindows::initSockets_(){
    WSADATA wsaData;
    int init = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (init < 0) {
        std::cerr << "Init error" << endl;
    }
}

void ServerWindows::createSocket_(){
    int newSocket = socket(AF_INET, SOCK_STREAM, 0);
    setServerSocket_(newSocket);
    if(getServerSocket_() < 0){
        cerr << "Create socket error" << endl;
    }
}

void ServerServerWindowsLinux::defineServerAddress_(int port){
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY make socket listen all avalible IPs
    serverAddress.sin_port = htons(port); //define server port
}

void ServerWindows::bindSocket_(){
    int bindSocket = bind(getServerSocket_(), (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if(bindSocket < 0){
        cerr << "Bind socket error" << endl;
    }
}

void ServerWindows::listenSocket_(int numOfConnect){
    int listener = listen(getServerSocket_(), numOfConnect); //numOfConnect is max value of connections can be in line
    if(listener < 0){
        cerr << "Listen error" << endl;
    }
    cout << "Server is started!" << endl;
}

void ServerWindows::acceptSocket_(){
    int newSocket = accept(getServerSocket_(),nullptr,nullptr);
    setClientSocket_(newSocket);
    if(getClientSocket_() < 0){
        cerr << "Connecting error" << endl;
    }
    cout << "Client connected!" << endl;
}

int ServerWindows::getMessage_(){
    int messageLenth = recv(getClientSocket_(), getBuffer_(), getBufferSize_(),0);
    if(messageLenth  < 0){
        cerr << "Getting error" << endl;
        return -1;
    }
    cout << "Server got messaage: " << getBuffer_() << endl;
    return messageLenth;
}

void ServerWindows::sendMessage_(int messageLenth){
    int send_ = send(getClientSocket_(),getBuffer_(),messageLenth,0);
    if(send_  < 0){
        cerr << "Sending error" << endl;
    }   
}

void ServerWindows::closeSocket_(){
  closesocket(getClientSocket_());
  closesocket(getServerSocket_());
}
