#ifndef SERVER_LINUX_H
#define SERVER_LINUX_H
    
#include <unistd.h>  //for close()
#include <sys/socket.h> //for socket(), bind(), listen(), accept()
#include <netinet/in.h> //for identify adress
#include <fcntl.h>
#include "server.h"

using namespace std;
    
class ServerLinux : public Server{
  virtual void initSockets_() override;
  virtual void createSocket_() override;
  virtual void defineServerAddress_(int port) override;
  virtual void bindSocket_() override;
  virtual void listenSocket_(int numOfConnect) override;
  virtual void acceptSocket_() override;
  virtual int getMessage_(int client) override;
  virtual void sendMessage_(int messageLenth, int senderSocket) override;
  virtual void closeSockets_() override;
  virtual void closeClientSocket_(int socket) override;
  virtual void madeUnblock_(int socket) override;
  virtual void handleClient_() override;

  struct sockaddr_in serverAddress;
  fd_set readSockets;

};
    
#endif


