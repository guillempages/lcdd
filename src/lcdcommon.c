
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/select.h>

#ifdef __cplusplus
namespace lcd {
#endif

int sock_=-1;
struct sockaddr_in address_;

int sendCommand(char command, char param, const char * line, int length);
int pingServer(int timeout);

int getServer(int port, const char * addr,int timeout) {
  
  if (sock_>=0) close(sock_);
  
  sock_=socket(PF_INET, SOCK_DGRAM, 0);
  
  if (sock_<0)
    return sock_;

  struct hostent *phe;


  address_.sin_family=AF_INET;
  address_.sin_port=htons(port);

  if ( phe=gethostbyname(addr) )
    memcpy((char *)&address_.sin_addr, phe->h_addr, phe->h_length);
  else if ( (address_.sin_addr.s_addr = inet_addr(addr)) == INADDR_NONE ) {
    close(sock_);
    errno=EADDRNOTAVAIL;
    return -2;
  }

	if (pingServer(timeout)<0) {
		return -3;
	}

  return sock_;
}

int closeServer() {
  int result=close(sock_);
  sock_=-1;
  return result;
}

int pingServer(int timeoutValue) {
	struct timeval timeout;
	fd_set socket;
	int error;
  struct sockaddr_in local;

  local.sin_family=AF_INET;
  local.sin_addr.s_addr=INADDR_ANY; 
  local.sin_port=0;

	if (sock_<0) {
    errno=ENOTCONN;
    return -1;
  }

  if (bind(sock_,(struct sockaddr *)&local, sizeof(local))<0) {
    return -1;
  }

	FD_ZERO(&socket);
  FD_SET(sock_,&socket);
	timeout.tv_sec=timeoutValue;
	timeout.tv_usec=0;
	
  char buffer[10];

	sendCommand('p','i',"ng",2);
	
	error=select(sock_+1,&socket,NULL,NULL,&timeout);
	if (!error) {
    errno=ETIMEDOUT;
    return -1;
  } else {
    error=recvfrom(sock_,buffer,4,0,NULL,0);
    if ((error<4) || 
        ((error>=5) && (buffer[4]!='\0')) ||
        (strcmp(buffer,"pong"))) {
       errno=EAGAIN;
       return -1;
    } else {
      return 1;
    }
  }
}

int sendLine1(const char* line,int length) {
  if (sock_<0) {
    errno=ENOTCONN;
    return -1;
  }
  int error;
  error=sendCommand('s','1',line,length);

  if (error < 0) {
    switch (error) {
    case -1:
      break;
    case -2:
      errno=EMSGSIZE;
      break;
    }
  }
  return error;
}

int sendLine2(const char* line,int length) {
  if (sock_<0) {
    errno=ENOTCONN;
    return -1;
  }
  int error;
  error=sendCommand('s','2',line,length);

  if (error < 0) {
    switch (error) {
    case -1:
      break;
    case -2:
      errno=EMSGSIZE;
      break;
    }
  }
  return error;
}

int sendCommand(char command, char param, const char * line, int length) {

  if (length>256) {
    return -2;
  }

  char * buffer = (char *) calloc((length+3),sizeof(char));

  if (buffer==0) {
    return -1;
  }

  buffer[0]=command;
  buffer[1]=param;
  if (length>0)
    memcpy(buffer+2,line,length);
  
  return sendto(sock_,buffer,length+2,0,(struct sockaddr *)&address_,sizeof(address_));
}

#ifdef __cplusplus
}; //namespace
#endif
