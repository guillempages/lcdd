#ifdef HAVE_CONFIG_H
#include "defines.h"
#endif

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using std::string;

#include <lcd>

int main(int argc,char * argv[]) {

  int port=11111;
  char server[]="127.0.0.1";
  char device[]="/dev/lcd0"; //should the server not be running  
  int timeoutValue=3; //seconds to wait for server to be ready

  // Check arguments...
  if (argc>1) {
    if ((string(argv[1])=="-v") || (string(argv[1])=="--version")) {
      std::cout << PACKAGE_NAME << " Version " << VERSION << std::endl;
      exit(0);
    }
  }

  bool serverOnline=false;
  if (__lcd::getServer(port,server,timeoutValue)<0) {
    perror("getServer error");
    serverOnline=false;
  } else {
    serverOnline=true;
  }

  string line1="",line2="";
  
  if (argc>=2) {
    line1+=argv[1];
    if (serverOnline) {
      int error;
      if ((error=__lcd::lcd_SendLine(1,line1.c_str(),line1.length()))<0) {
        std::cout << "SendLine1 returned " << error << std::endl;
        perror("sendLine1 error");
      }
    }
  }
  if (argc>=3) {
    line2+=argv[2];
    if (serverOnline) {
      int error;
      if ((error=__lcd::lcd_SendLine(2,line2.c_str(),line2.length()))<0) {
        std::cout << "SendLine2 returned " << error << std::endl;
        perror("sendLine2 error");
      }
    }
  }
  
  //if the server is not running (or does not answer), 
  //do it ourselves. Just write to the device
  if (!serverOnline) {
    string line=line1;
    line.resize(16,' '); //no server->no scrolling; just cut
    line+=line2;
    line.resize(32,' '); //ditto
    std::ofstream lcd(device,std::ios::out);
    lcd << line;
    lcd.close();
  }
  return 0;
}
