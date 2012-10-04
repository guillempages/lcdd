#ifdef HAVE_CONFIG_H
#include "defines.h"
#endif

#include <iostream>

#include <lcd>

using std::cout;
using std::cerr;
using std::endl;

extern int sendCommand(char,char,const char *, int);

int main(int argc, char * argv[]) {

  int result=0;
cerr <<"Begin" << endl;
  LCD lcd;
cerr << "Constructor done" << endl;
  if (! lcd.connected()) {
    cerr << "Could not connect to server" << endl;
    exit (1);
  }

  
  cerr << "Testing static text" << endl;

  if (lcd.sendLine("static text (1)",1) < 0) {
    perror ("Could not write static text to first line");
    result=1;
  }
  if (lcd.sendLine("static text (2)",2) < 0) {
    perror ("Could not write static text to second line");
    result=1;
  }

  sleep(1);

  printf("Testing scrolling text\n");

  if (lcd.sendLine("scrolling text (1)",1) < 0) {
    perror ("Could not write scrolling text to first line");
    result=1;
  }
  if (lcd.sendLine("scrolling text (2)",2) < 0) {
    perror ("Could not write scrolling text to second line");
    result=1;
  }

  return (result);
}
