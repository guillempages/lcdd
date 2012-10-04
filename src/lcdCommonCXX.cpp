
#include <string>
#include <lcd>

namespace __lcd {
#include "lcdCommon.c"
}

using std::string;
using namespace __lcd;

LCD::LCD(const string & server, int port, bool cleanOnExit) :
  server_(server),
  port_(port),
  connected_(false),
  cleanOnExit_(cleanOnExit)
{
  connect(server_,port_,1);
}

int LCD::connect(const std::string & server, int port, int timeout) {
  if (server != "") {
    server_=server;
  }
  if ( port >= 0) {
    port_=port;
  }

  connected_=lcd_GetServer(port,server.c_str(),timeout);

  return connected_;
}

int LCD::sendLine(const string & text,int line) {
  if (!connected_) {
    connect();
  }
  if (!connected_) {
    return -1;
  } else {
    return lcd_SendLine(line,text.c_str(),text.length());
  }
}

int LCD::ping(int timeout) {
  if (!connected_) {
    connect();
  }
  if (!connected_) {
    return -1;
  } else {
    return lcd_PingServer(timeout);
  }
}
