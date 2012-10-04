
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <netinet/in.h>

int createSocket() {
  return socket(PF_INET, SOCK_DGRAM, 0);
}

int bindSocket(int sock, struct sockaddr_in* addr) {

  struct sockaddr_in addrtmp=*addr;
  return bind(sock,(struct sockaddr *)addr,sizeof(addrtmp));
}

int sendToSocket(int sock, const char * buffer, size_t bufferlen, struct sockaddr_in *remote) {
  struct sockaddr_in addrtmp=*remote;
  return sendto(sock,buffer,bufferlen,0,(struct sockaddr *)remote,sizeof(addrtmp));
}
