#include <iostream>
#include <cstring>
#include "server.h"

using namespace std;

int main(){

    Server* server = Server::createServer_();
    server->startServer_(12345);

  return 0;
}
