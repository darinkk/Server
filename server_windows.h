#ifndef SERWER_WINDOWS_H
#define SERWER_WINDOWS_H

#include <winsock2.h>     // для Windows сокетів
#include <ws2tcpip.h>
#include "server.h"

class ServerWindows : public Server{
//private:
  virtual void initSockets_() override;
  virtual void createSocket_() override;
  virtual void defineServerAddress_(int port) override;
  virtual void bindSocket_() override;
  virtual void listenSocket_(int numOfConnect) override;
  virtual void acceptSocket_() override;
  virtual int getMessage_() override;
  virtual void sendMessage_(int messageLenth) override;
  virtual void closeSockets_() override;

  struct sockaddr_in serverAddress;
}; 

#endif
