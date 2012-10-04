#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using std::string;

#include <arpa/inet.h>

#include "auxfunctions.h"


int main(int argc,char * argv[]) {

  int sock=createSocket();
  int port=11111;

  struct sockaddr_in remote;

  remote.sin_family=AF_INET;
  remote.sin_port=htons(port);
  remote.sin_addr.s_addr=inet_addr("127.0.0.1");

  string line1="",line2="";

	if (argc>=2) {
    line1+=argv[1];
  }

  if (argc>=3) {
    line2+=argv[2];
  }

	if (sendToSocket(sock,"test",5,&remote)<0) {
		std::ofstream lcd("/dev/lcd",	std::ios::out);
		line1.resize(16,' ');
		line1+=line2;
		line1.resize(32,' ');
		lcd << line1;
		lcd.close();
		exit(1);
	}
	perror("error?"); 
 
	line1="1"+line1;
	line2="2"+line2;

  if (sendToSocket(sock,line1.c_str(),line1.length(),&remote)<0)
    perror("lcdwrite error:");
  if (sendToSocket(sock,line2.c_str(),line2.length(),&remote)<0)
    perror("lcdwrite error:");
  
  return 0;
}
