#ifndef SERVER_H
#define SERVER_H

class Server{
public:
  Server();
  ~Server();
  static Server* createServer_();
  void startServer_(int port);
  void stopServer() {closeSockets_();}
  int getServerSocket_(){return serverSocket;}
  void setServerSocket_(int newSerSock){serverSocket = newSerSock;}
  int getClientSocket_(){return clientSocket;}
  void setClientSocket_(int newCliSock){clientSocket = newCliSock;}
  char* getBuffer_(){return buffer;}
  int getBufferSize_(){return sizeof(buffer);}
  
private:
  virtual void initSockets_() = 0;
  virtual void createSocket_() = 0;
  virtual void defineServerAddress_(int port) = 0;
  virtual void bindSocket_() = 0;
  virtual void listenSocket_(int numOfConnect) = 0;
  virtual void acceptSocket_() = 0;
  virtual int getMessage_() = 0;
  virtual void sendMessage_(int messageLenth) = 0;
  virtual void closeSockets_() = 0;

  char buffer[1024];
  int serverSocket;
  int clientSocket;
};

#endif
