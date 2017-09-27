#ifndef REQUEST_H
#define  REQUEST_H
#include <iostream>
using namespace std;
#include <string.h>
#include <map>
class Request{
private:
  string body;
  string method;
  string path;
  string protocol;
  string content;
  string postfix;
  map<string,string> headers;
  map<string,string> params;
public:
  Request();
  ~Request();
  void setBody(string body);
  bool parse();
  string getMethod();
  string getPath();
  string getProtocol();
  string getContent();
  string getPostfix();
  map<string,string> getParam();
  map<string,string> getHeaders();
};
#endif
