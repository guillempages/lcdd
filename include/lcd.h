#ifndef LCD_H
#define LCD_H

//c interface
int lcd_GetServer(int port, const char * addr,int timeout);

int lcd_CloseServer();
int lcd_PingServer(int timeout);

int lcd_SendLine(int line, const char* text,int length);
//int sendLine1(char* line,int length);
//int lcd_SendLine2(const char* line,int length);
//int sendLine2(char* line,int length);

#ifdef __cplusplus
#ifndef LCD_H_CPP
#error "For c++ programs, please include <lcd> and not <lcd.h>"
#endif

#endif //__cplusplus
inline int getServer(int port, const char * addr,int timeout) {
  lcd_GetServer(port,addr,timeout);
}

inline int closeServer() { lcd_CloseServer(); }
inline int pingServer(int timeout) { lcd_PingServer(timeout); }

inline int sendLine1( const char* text,int length) {lcd_SendLine(1,text,length); }
inline int sendLine2( const char* text,int length) {lcd_SendLine(2,text,length); }

#endif
