#ifndef XTCP_H
#define XTCP_H
#include <iostream>
using namespace std;

class XTcp{
private:
  int sock;

public:
  XTcp();
  void setSock(int sock);
  int getSock();
  int createSocket();
  int bindPort(unsigned short port);
  int listenSocket();
  int receive(char *buf,int len);
  int sendData(const char *buf,int len);
  bool connectServer(int port);
  XTcp* acceptClient();
  int closeSocket();
  bool SetBlock(bool isblock);
  ~XTcp();
};
#endif
