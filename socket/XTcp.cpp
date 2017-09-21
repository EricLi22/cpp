#include "XTcp.h"
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
#include <thread>
#include "XThread.h"
XTcp::XTcp(){
        //创建一个socket
        sock=-1;
}

void XTcp::setSock(int sock){
        this->sock=sock;
}
int XTcp::getSock(){
        return this->sock;
}

int XTcp::createSocket(){
        this->sock=socket(AF_INET,SOCK_STREAM,0);
        if(this->sock==-1) {
                cout<<"create socket failed"<<endl;
        }
        return this->sock;
}
int XTcp::bindPort(unsigned short port){
        struct sockaddr_in sockaddr;
        memset(&sockaddr,0,sizeof(sockaddr));
        sockaddr.sin_family=AF_INET;
        sockaddr.sin_addr.s_addr=htonl(INADDR_ANY);
        sockaddr.sin_port=htons(port);
        ::bind(sock,(struct sockaddr *)&sockaddr,sizeof(sockaddr));
        return 0;
}

int XTcp::listenSocket(){
        listen(sock,10);
        return 0;
}

/**
 *  接受客户端的连接，如果连接成功就返回连接后的XTcp
 */
XTcp* XTcp::acceptClient(){
        int connfd;
        struct sockaddr_in sockaddrClient;
        int clientl=sizeof(sockaddrClient);
        printf("wait for client connect\n" );
        // if((connfd = accept(sock,NULL,NULL))==-1) {
        if((connfd = accept(sock,(struct sockaddr*)&sockaddrClient,(socklen_t *)&clientl))==-1) {
                printf("accpet socket error: %s errno :%d\n",strerror(errno),errno);
        }
        char cilentIp[20];
        unsigned short port= ntohs(sockaddrClient.sin_port);
        const char *ip=inet_ntop(AF_INET,(void *)&sockaddrClient.sin_addr,cilentIp,16);
        printf("client=> %s:%d\n",cilentIp,port);
        XTcp* xTcpClient=new XTcp;
        xTcpClient->setSock(connfd);
        //开启线程接受数据
        XThread* st=new XThread(xTcpClient);
        thread t(&XThread::run,st);
        t.detach();
        return xTcpClient;
}

int XTcp::connectServer(int port){
        const char * serverIp="127.0.0.1";
        sockaddr_in sockaddr;
        memset(&sockaddr,0,sizeof(sockaddr));
        sockaddr.sin_family = AF_INET;
        sockaddr.sin_port = htons(port);
        //转换ip地址
        inet_pton(AF_INET,serverIp,&sockaddr.sin_addr);
        if((connect(sock,(struct sockaddr*)&sockaddr,sizeof(sockaddr))) < 0 )
        {
                printf("connect error :[%s] errno: %d\n",strerror(errno),errno);
                exit(0);
        }
        cout<<"send msg to server:"<<endl;
        char buf[1024];
        while (true) {
                /* code */
                fgets(buf,1024,stdin);
                if(strcmp(buf,"exit\n")==0) {
                        //输入exit后退出
                        break;
                }
                int size=sendData(buf,sizeof(buf));
                //写数据是发生异常
                if(size<=0) {
                        break;
                }
        }
        //关闭客户端socket
        closeSocket();
}

/*
 *  接受数据
 */
int XTcp::receive(char *buf,int len){
        int n = recv(this->sock,buf,len,0);
        return n;
}

/**
* 发送数据
*/
int XTcp::sendData(char *buf,int len){
        if(sock<0) {
                cout<<"socket is invalid"<<endl;
                return -1;
        }
        if(len<=0) {
                return 0;
        }
        int totalSize=0;
        while (totalSize<len) {
                /* code */
                int size=send(sock,buf+totalSize,strlen(buf)-totalSize,0);
                if(size<=0)
                        break;
                totalSize+=size;
        }
        return totalSize;
}

/**
 * 关闭socket
 */
int XTcp::closeSocket(){
        int ret=0;
        if(sock==-1) {
                cout<<"socket is not start"<<endl;
        }else if(sock==-1) {
                cout<<"socket have already closed"<<endl;
        }else{
                ret  =close(sock);
                if(ret==-1) {
                        printf("socket close failed\n");
                }else{
                        printf("%d close success!\n",sock );
                }
        }
        sock=-2;
        return ret;
}

XTcp::~XTcp(){
        cout<<"~XTcp"<<endl;
}
