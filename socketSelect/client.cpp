#include "XTcp.h"
#include "iostream"

using namespace std;

int main(int argc,char **argv){
  unsigned short port=8888;
  if(argc>1){
    port=atoi(argv[1]);
  }
  cout<<"port:"<<port<<endl;
  XTcp xtcp;
  xtcp.createSocket();
  bool res=xtcp.connectServer(8888);
  char* data="GET / HTTP/1.0";
  if(res){
    xtcp.sendData(data,sizeof(data));
  }else{
    xtcp.closeSocket();
  }
}
