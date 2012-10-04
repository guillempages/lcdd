#ifndef CTHINGS_H
#define CTHINGS_H


#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

extern "C" {
  int createSocket();

  int bindSocket(int sock, struct sockaddr_in * addr);
  
  int sendToSocket(int sock, const char * buffer, size_t bufferlen, struct sockaddr_in *remote);
}

#endif
