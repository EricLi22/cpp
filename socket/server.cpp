#include "stdio.h"
//socket相关函数需要
#include <sys/types.h>
#include <sys/socket.h>
//close函数需要
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include "SocketThread.h"
#include <thread>
#include <functional>
#include <iostream>
using namespace std;
#define MAXLINE 1024

int main(){
        int connfd;
        char buff[MAXLINE];
        int n;
        SocketThread* st=new SocketThread(1);
        thread t(&SocketThread::Main,st);
        //创建一个socket
        int sock=socket(AF_INET,SOCK_STREAM,0);
        if(sock==-1) {
                printf("create socket failed\n" );
        }
        printf("create socket success! %d\n", sock);
        struct sockaddr_in sockaddr;
        memset(&sockaddr,0,sizeof(sockaddr));
        sockaddr.sin_family=AF_INET;
        sockaddr.sin_addr.s_addr=htonl(INADDR_ANY);
        sockaddr.sin_port=htons(9999);
        bind(sock,(struct sockaddr *)&sockaddr,sizeof(sockaddr));
        listen(sock,1024);
        printf("please wait for client information\n" );
        char cilentIp[20];
        while (true) {
                /* code */
                struct sockaddr_in sockaddrClient;
                int clientl=sizeof(sockaddrClient);
                // if((connfd = accept(sock,NULL,NULL))==-1) {
                if((connfd = accept(sock,(struct sockaddr*)&sockaddrClient,(socklen_t *)&clientl))==-1) {
                        printf("accpet socket error: %s errno :%d\n",strerror(errno),errno);
                }
                unsigned short port= ntohs(sockaddrClient.sin_port);
                const char *ip=inet_ntop(AF_INET,(void *)&sockaddrClient.sin_addr,cilentIp,16);
                printf("client %s:%d\n",cilentIp,port);
                for(;; ) {
                        n = recv(connfd,buff,1024,0);
                        if(n<=0) {
                                //如果客户端断开了，这里就跳出循环
                                // printf("rece %d\n",n);
                                break;
                        }
                        buff[n] = '\0';
                        printf("%d=>%s",n,buff);
                }
                close(connfd);
        }

        int ret=close(sock);
        if(ret==-1) {
                printf("socket close failed\n");
        }else{
                printf("%d close success!\n",sock );
        }
        return 0;
}
