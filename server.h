#ifndef SERVER_H
#define SERVER_H

class Server{
public:
  Server();
  virtual void initSockets_() = 0;
  virtual void createSocket_() = 0;
  virtual void defineServerAddress_(int port) = 0;
  virtual void bindSocket_() = 0;
  virtual void listenSocket_(int numOfConnect) = 0;
  virtual void acceptSocket_() = 0;
  virtual int getMessage_() = 0;
  virtual void sendMessage_(int messageLenth) = 0;
  virtual void closeSockets_() = 0;
  static Server* createServer_();
  
protected:
  char buffer[1024];
  int serverSocket;
  int clientSocket;
};

#endif
