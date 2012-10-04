#ifndef LCD_H
#define LCD_H

#ifdef __cplusplus
#ifndef LCD_H_CPP
#error "For c++ programs, please include <lcd> and not <lcd.h>"
#endif
#endif

int getServer(int port, const char * addr,int timeout);

//inline int getServer(int port, const char * addr,int timeout) {
 // return getServer(port,addr,timeout);
//}

int closeServer();
int pingServer(int timeout);

int sendLine1(const char* line,int length);
//int sendLine1(char* line,int length);
int sendLine2(const char* line,int length);
//int sendLine2(char* line,int length);

#endif
