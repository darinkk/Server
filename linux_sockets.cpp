#ifdef __linux__
#include "socket.h"
#include <iostream>
#include <unistd.h>  //for close()
#include <sys/socket.h> //for socket(), bind(), listen(), accept()
#include <netinet/in.h> //for identify adress

void initSockets_(){
  
}

void closeSocket_(int socket){
  close(socket);
}

#endif
