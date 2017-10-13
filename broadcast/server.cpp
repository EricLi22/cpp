#include <iostream>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define BUFF_LEN 1024
int main(int argc,char **argv){
        int port=8888;
        if(argc>1){
          port=atoi(argv[1]);
        }
        cout<<INADDR_ANY<<":"<<port<<endl;
        int sock=socket(AF_INET,SOCK_DGRAM,0);
        int ret=0;
        sockaddr_in addr;
        addr.sin_family=AF_INET;
        //本地Ip
        addr.sin_addr.s_addr=htonl(INADDR_ANY);
        addr.sin_port=port;
        //设置该套接字为广播类型，
        const int opt = 1;
        int nb = 0;
        nb = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
        if(nb == -1)
        {
                cout<<"set setsockopt error..."<<endl;
                return false;
        }
        ret=bind(sock,(sockaddr*)&addr,sizeof(addr));
        if(ret<0) {
                cout<<"bind failed"<<endl;
        }
        char buf[BUFF_LEN]; //接收缓冲区，1024字节
        int recvRet;
        sockaddr_in clientAddr;
        socklen_t len=sizeof(clientAddr);
        char clientIp[16]={0};
        while (true) {
                /* code */
                memset(buf,0,BUFF_LEN);
                //0表示对方关闭，-1为发生错误。
                recvRet=recvfrom(sock,buf,BUFF_LEN,NULL,(sockaddr *)&clientAddr,&len);
                if(recvRet<=0) {
                        cout<<"receive failed"<<endl;
                        break;
                }else{
                        memset(clientIp,0,sizeof(clientIp));
                        int clientPort=ntohs(clientAddr.sin_port);
                        inet_ntop(AF_INET,(void *)&clientAddr.sin_addr,clientIp,16);
                        cout<<"receive data from "<<clientIp<<":"<<clientPort<<endl;
                        cout<<buf<<endl;
                }
        }
        if(sock>0) {
                close(sock);
        }
        return 0;
}
