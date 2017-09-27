#ifndef RESPONSE_H
#define  RESPONSE_H
#include <iostream>
using namespace std;
#include <map>
#include <string.h>

class Response{
private:
  int code;
  string msg;
  string protocol;
  map<string,string> headers;
public:
  Response();
  ~Response();
  void setCode(int code);
  void setMsg(const char* msg);
  void setProtocol(const char protocol);
  void addHead(string,string);
  void setContentLength(int length);
  string getData();
};
#endif
