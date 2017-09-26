#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H
#include "iostream"
using namespace std;
#include "XTcp.h"

class HttpServer {
private:
  bool exit;
XTcp *server;
void run();
public:
bool start(unsigned short port);
HttpServer();
~HttpServer();
void setExit(bool exit);
};
#endif
