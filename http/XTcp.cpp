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
//c++ 11标准线程
#include <thread>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
XTcp::XTcp(){
        sock=-1;
}

void XTcp::setSock(int sock){
        this->sock=sock;
}
int XTcp::getSock(){
        return this->sock;
}

int XTcp::createSocket(){
        //创建一个socket
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

/**
 * 开始监听
 */
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
        if((connfd = accept(sock,(struct sockaddr*)&sockaddrClient,(socklen_t *)&clientl))==-1) {
                printf("accpet socket error: [%s] errno :%d\n",strerror(errno),errno);
                return NULL;
        }
        cout<<"connfd "<<connfd<<endl;
        char cilentIp[20];
        unsigned short port= ntohs(sockaddrClient.sin_port);
        const char *ip=inet_ntop(AF_INET,(void *)&sockaddrClient.sin_addr,cilentIp,16);
        printf("client=> %s:%d\n",cilentIp,port);
        XTcp* xTcpClient=new XTcp;
        xTcpClient->setSock(connfd);
        return xTcpClient;
}

bool XTcp::connectServer(int port){
        const char * serverIp="127.0.0.1";
        sockaddr_in sockaddr;
        memset(&sockaddr,0,sizeof(sockaddr));
        sockaddr.sin_family = AF_INET;
        sockaddr.sin_port = htons(port);
        //转换ip地址
        inet_pton(AF_INET,serverIp,&sockaddr.sin_addr);
        int ss=SetBlock(false);
        fd_set set;
        cout<<"start connect "<<sock<<endl;
        //!=0代表未连接成功
        if((connect(sock,(struct sockaddr*)&sockaddr,sizeof(sockaddr))) != 0 )
        {
                printf("connect error :[%s] errno: %d\n",strerror(errno),errno);
                cout<<"=>select"<<endl;
                //清空fdset与所有文件描述符的联系。
                FD_ZERO(&set);
                //建立文件描述符fd与fdset的联系。
                FD_SET(sock,&set);
                timeval tm;
                tm.tv_sec = 3;
                tm.tv_usec = 0;
                //这三个参数都是描述符的集合，
                //第一个rfds是用来保存这样的描述符的：当描述符的状态变成可读的时系统就会告诉select函数返回，
                //第二个wfds是指有描述符状态变成可写的时系统就会告诉select函数返回，
                //第三个参数efds是特殊情况，即描述符上有特殊情况发生时系统会告诉select函数返回
                int res=select(sock+1,NULL,&set,NULL,&tm);
                cout<<"<=select res: "<<res<<endl;
                //select返回0,则表示建立连接超时;我们返回超时错误给用户,同时关闭连接,以防止三路握手操作继续进行下去;
                //On error, -1 is returned
                if( res<= 0)
                {
                        printf("connect timeout or error!\n");
                        return false;
                }
                //检查fd_set联系的文件描述符fd是否可读写，>0表示可读写。
                if ( !FD_ISSET( sock, &set ) )
                {
                        printf( "no events on sockfd found\n" );
                        return false;
                }
                int error = 0;
                socklen_t length = sizeof( error );
                //获取任意类型、任意状态套接口的选项当前值
                if( getsockopt( sock, SOL_SOCKET, SO_ERROR, &error, &length ) < 0 )
                {
                        printf( "get socket option failed\n" );
                        return false;
                }
                if( error != 0 )
                {
                        printf( "connection failed after select with the error:[%s] errno %d \n",strerror(error), error );
                        return false;
                }
        }
        cout<<"connect success"<<endl;
        SetBlock(true);
        return true;
}

bool XTcp::SetBlock(bool isblock)
{
        if(sock<=0) return false;
        //F_GETFL 取得文件描述符状态
        int flags = fcntl(sock,F_GETFL,0);
        //如果出错，所有命令都返回－1，如果成功则返回某个其他值
        if(flags<0)
                return false;
        if(isblock)
        {
                //设置阻塞模式
                flags = flags&~O_NONBLOCK;
        }
        else
        {
                flags = flags|O_NONBLOCK;
        }
        if(fcntl(sock,F_SETFL,flags)!=0)
                return false;
        return true;
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
int XTcp::sendData(const char *buf,int len){
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
