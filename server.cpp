#include "server.h"
#include <iostream>
#ifdef __linux__
  #include "server_linux.h"
#elif _WIN32
  #include "server_windows.h"
#else
#endif

using namespace std;

Server::Server(){
  //fill(buffer, buffer+1024,0);
  cleanBuffer_();
  cleanClientSockets_();
}

Server* Server::createServer_(){
  #ifdef __linux__
    return new ServerLinux;
  #elif _WIN32
    return new ServerWindows;
  #else
    return nullptr;
  #endif
}

void Server::startServer_(int port){
  initSockets_();
  createSocket_();
  defineServerAddress_(port);
  bindSocket_();
  listenSocket_(3);
  madeUnblock_(serverSocket);
  //while(clientSockets.size() > 0){handleClient_();}
  handleClient_();
  }

  



