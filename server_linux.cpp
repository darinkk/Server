#include "server_linux.h"
#include <iostream>
#include <algorithm>

using namespace std;

void ServerLinux::initSockets_(){ }

void ServerLinux::createSocket_(){
    int newSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(newSocket < 0){
        cerr << "Create socket error" << endl;
    }
    setServerSocket_(newSocket);
}

void ServerLinux::defineServerAddress_(int port){
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY make socket listen all avalible IPs 
    serverAddress.sin_port = htons(port); //define server port
}

void ServerLinux::bindSocket_(){
    int bindSocket = bind(getServerSocket_(), (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if(bindSocket < 0){
        cerr << "Bind socket error" << endl;
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
    if(newSocket < 0){
        //cerr << "Connecting error" << endl;
    }else{
        madeUnblock_(newSocket);
        getClientSockets_().push_back(newSocket);
        //FD_SET(newSocket, &readSockets); //jnj
        cout << "Client connected! " << endl;
    }

}

int ServerLinux::getMessage_(int client){
    int messageLenth = recv(client, getBuffer_(), getBufferSize_(),0);
    if(messageLenth  <= 0){
        cerr << "Getting error" << endl;
        closeClientSocket_(client);
        return messageLenth;
    }
    cout << "Server got messaage: " << getBuffer_() << endl;
    return messageLenth;
}

void ServerLinux::sendMessage_(int messageLenth, int senderSocket){
    for(int client : getClientSockets_()){
        if(client != senderSocket){
            int send_ = send(client,getBuffer_(),messageLenth,0);
            if(send_  < 0){
                cerr << "Sending error" << endl;
            } 
        }
    } 
}

void ServerLinux::closeSockets_(){
    close(getServerSocket_());
    for (int clientSocket : getClientSockets_()) {
        close(clientSocket);
    }
}

void ServerLinux::closeClientSocket_(int socket){ close(socket); }

void ServerLinux::madeUnblock_(int socket){fcntl(socket, F_SETFL, O_NONBLOCK);}

void ServerLinux::handleClient_(){
    while(true){
        FD_ZERO(&readSockets); //clean
        FD_SET(getServerSocket_(), &readSockets); //add serverSocket to readSockets
        int maxFileDescriptor = getServerSocket_();

        int isSet = FD_ISSET(getServerSocket_(),&readSockets);
        if( isSet > 0 ){ acceptSocket_(); } //Check if is new connection

        for(int client: getClientSockets_()){
            FD_SET(client, &readSockets);
            if(client > maxFileDescriptor){maxFileDescriptor = client;};
        }

        int activity = select(maxFileDescriptor + 1,&readSockets,nullptr,nullptr,nullptr); //wait for activity
        if(activity < 0){cerr << "Activity error" << endl; break;}

        std::vector<int> activeClients;

        if(getClientSockets_().size() > 0){
            for(auto i = getClientSockets_().begin(); i != getClientSockets_().end();){
            int client = *i;
            //cout << "Checking activity on client: " << client << endl;
            if(FD_ISSET(client, &readSockets)){ 
                cleanBuffer_();
                int messageLength = getMessage_(client); 
                if(messageLength < 0){
                    closeClientSocket_(client);
                    cout <<"client: " << client << "disconected!";
                    i = getClientSockets_().erase(i);
                    //if(getClientSockets_().size == 0) {break;}
                }
                else { 
                    sendMessage_(messageLength,client);
                    ++i;
                }
            }else{
                ++i;
            }
        }
        }

    }
}



