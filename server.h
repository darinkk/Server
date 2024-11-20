#ifndef SERVER_H
#define SERVER_H
#include <vector>


class Server{
public:
  Server();
  ~Server();
  static Server* createServer_();
  void startServer_(int port);
  void stopServer() {closeSockets_();}
  int getServerSocket_(){return serverSocket;}
  void setServerSocket_(int newSerSock){serverSocket = newSerSock;}
  std::vector<int> &getClientSockets_(){return clientSockets;} //New
  void setClientSocket_(int newCliSock){clientSockets.push_back(newCliSock);} //Chenged
  char* getBuffer_(){return buffer;}
  int getBufferSize_(){return sizeof(buffer);}
  void cleanBuffer_(){std::fill(buffer, buffer+1024,0);} 
  void cleanClientSockets_(){clientSockets.clear();}
  
private:
  virtual void initSockets_() = 0;
  virtual void createSocket_() = 0;
  virtual void defineServerAddress_(int port) = 0;
  virtual void bindSocket_() = 0;
  virtual void listenSocket_(int numOfConnect) = 0;
  virtual void acceptSocket_() = 0;
  virtual int getMessage_(int client) = 0;
  virtual void sendMessage_(int messageLenth, int senderSocket) = 0;
  virtual void closeSockets_() = 0;
  virtual void closeClientSocket_(int socket) = 0;
  virtual void handleClient_() = 0;
  virtual void madeUnblock_(int socket) = 0;

  char buffer[1024];
  int serverSocket;
  std::vector<int> clientSockets;
};

#endif
