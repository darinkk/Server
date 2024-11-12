#include <iostream>
#include <cstring>
#include <unistd.h>  //for close()
#include <sys/socket.h> //for socket(), bind(), listen(), accept()
#include <netinet/in.h> //for identify adress


using namespace std;

int main(){
    //Create socket
    //AF_INET - specified type of adress like IPv4, SOCK_STEAM - defines type of socket like stream socket, 0 - defines type of protocol like default (TCP)
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket < 0){
        cerr << "Create socket error" << endl;
        return -1;
    }

    //Define server address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY make socket listen all avalible IPs
    serverAddress.sin_port = htons(12345); //define server port

    //Binding socket to server address
    int bindSocket = bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if(bindSocket < 0){
        cerr << "Bind socket error" << endl;
        return -1;
    }

    //Waiting for connection
    int listener = listen(serverSocket, 5); //5 is max value of connections can be in line
    if(listener < 0){
        cerr << "Listen error" << endl;
        return -1;
    }
    cout << "Server is started!" << endl;

    //Accepting client connection
    int clientSocket = accept(serverSocket,nullptr,nullptr);
    if(clientSocket < 0){
        cerr << "Connecting error" << endl;
        return -1;
    }
    cout << "Client connected!" << endl;

    //Getting message
    char buffer[1024] = {0};
    int get = recv(clientSocket, buffer, sizeof(buffer),0);
    if(get < 0){
        cerr << "Getting error" << endl;
        return -1;
    }
    cout << "Server got messaage: " << buffer << endl;

    //Answer
    int send_ = send(clientSocket,buffer,get,0);
    if(send_ < 0){
        cerr << "Sending error" << endl;
    }


    //Close connection
    close(clientSocket);
    close(serverSocket);

  return 0;
}