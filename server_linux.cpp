#include "server_linux.h"
#include <iostream>
#include <cerrno>
#include <cstring>

using namespace std;

void ServerLinux::initSockets_(){ }

void ServerLinux::createSocket_(){
    int newSocket = socket(AF_INET, SOCK_STREAM, 0);
    setServerSocket_(newSocket);
    if(getServerSocket_() < 0){
        cerr << "Create socket error" << endl;
    }
}

void ServerLinux::defineServerAddress_(int port){
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY make socket listen all avalible IPs
    serverAddress.sin_port = htons(port); //define server port
}

void ServerLinux::bindSocket_(){
    int bindSocket = bind(getServerSocket_(), (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if(bindSocket < 0){
        cerr << "Bind socket error" << strerror(errno) << endl;
    }
}

void ServerLinux::listenSocket_(int numOfConnect){
    int listener = listen(getServerSocket_(), numOfConnect); //numOfConnect is max value of connections can be in line
    if(listener < 0){
        cerr << "Listen error" << endl;
    }
    cout << "Server is started!" << endl;
}

void ServerLinux::acceptSocket_(){
    int newSocket = accept(getServerSocket_(),nullptr,nullptr);
    setClientSocket_(newSocket);
    if(getClientSocket_() < 0){
        cerr << "Connecting error" << endl;
    }
    cout << "Client connected!" << endl;
}

int ServerLinux::getMessage_(){
    int messageLenth = recv(getClientSocket_(), getBuffer_(), getBufferSize_(),0);
    if(messageLenth  < 0){
        cerr << "Getting error" << endl;
        return -1;
    }
    cout << "Server got messaage: " << getBuffer_() << endl;
    return messageLenth;
}

void ServerLinux::sendMessage_(int messageLenth){
    int send_ = send(getClientSocket_(),getBuffer_(),messageLenth,0);
    if(send_  < 0){
        cerr << "Sending error" << endl;
    }   
}

void ServerLinux::closeSockets_(){
    close(getServerSocket_());
    close(getClientSocket_());
}


