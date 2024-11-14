
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
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket < 0){
        cerr << "Create socket error" << endl;
    }
}

void ServerServerWindowsLinux::defineServerAddress_(int port){
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY make socket listen all avalible IPs
    serverAddress.sin_port = htons(port); //define server port
}

void ServerWindows::bindSocket_(){
    int bindSocket = bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if(bindSocket < 0){
        cerr << "Bind socket error" << endl;
    }
}

void ServerWindows::listenSocket_(int numOfConnect){
    int listener = listen(serverSocket, numOfConnect); //numOfConnect is max value of connections can be in line
    if(listener < 0){
        cerr << "Listen error" << endl;
    }
    cout << "Server is started!" << endl;
}

void ServerWindows::acceptSocket_(){
    clientSocket = accept(serverSocket,nullptr,nullptr);
    if(clientSocket < 0){
        cerr << "Connecting error" << endl;
    }
    cout << "Client connected!" << endl;
}

int ServerWindows::getMessage_(){
    int messageLenth = recv(clientSocket, buffer, sizeof(buffer),0);
    if(messageLenth  < 0){
        cerr << "Getting error" << endl;
        return -1;
    }
    cout << "Server got messaage: " << buffer << endl;
    return messageLenth;
}

void ServerWindows::sendMessage_(int messageLenth){
    int send_ = send(clientSocket,buffer,messageLenth,0);
    if(send_  < 0){
        cerr << "Sending error" << endl;
    }   
}

void ServerWindows::closeSocket_(){
  closesocket(clientSocket);
  closesocket(serverSocket);
}
