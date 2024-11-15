#include "server.h"
#include <iostream>
#ifdef __linux__
  #include "server_linux.h"
#elif
  #include "server_windows.h"
#else
#endif

Server::Server(){
  std::fill(buffer, buffer+1024,0);
  serverSocket = -1;
  clientSocket = -1;
}

Server* Server::createServer_(){
  #ifdef __linux__
    return new ServerLinux;
  #elif
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
  listenSocket_(5);
  acceptSocket_();
  int messageLenth = getMessage_();
  sendMessage_(messageLenth);
  closeSockets_();
}

