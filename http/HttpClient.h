#ifndef HTTPCLIENT_H
#define  HTTPCLIENT_H
#include <iostream>
using namespace std;
#include "XTcp.h"

class HttpClient {

private:
XTcp* client;
void run();
public:
HttpClient(XTcp* client);
~HttpClient();
bool process();
};
#endif
