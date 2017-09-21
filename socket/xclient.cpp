#include <iostream>
using namespace std;
#include "XTcp.h"
#include <stdlib.h>

int main(int argc,char ** argv){
  unsigned short port=8888;
  if(argc>2){
    port=atoi(argv[1]);
  }
  XTcp client;
  client.createSocket();
  client.connectServer(port);
  return 0;
}
