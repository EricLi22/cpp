#include <iostream>
#include <stdlib.h>
#include <sys/epoll.h>
#include <string.h>
using namespace std;
#include "XTcp.h"
int main(int argc,char ** argv){
        unsigned short port=8888;
        if(argc>1) {
                port=atoi(argv[1]);
        }
        XTcp server;
        server.createSocket();
        server.bindPort(port);
        server.listenSocket();
        int epfd = epoll_create(256);
        //注册epoll事件
        struct epoll_event ev;
        ev.data.fd = server.getSock();
        //数据接入事件|边缘检测,ET模式仅当状态发生变化的时候才获得通知
        ev.events=EPOLLIN|EPOLLET;
        epoll_ctl(epfd,EPOLL_CTL_ADD,server.getSock(),&ev);

        struct epoll_event event[20];
        char buf[1024] = {0};
        const char *msg = "HTTP/1.1 200 OK\r\nContent-Length: 1\r\n\r\nX";
        int size = strlen(msg);
        server.SetBlock(false);
        while (true) {
                //检测事件
                int count = epoll_wait(epfd,event,20,500);
                if(count <=0) continue;
                for(int i = 0; i < count; i++)
                {
                        //连接事件发生
                        if(event[i].data.fd == server.getSock())
                        {
                                cout<<"<<= connect event"<<endl;
                                for(;; )
                                {
                                        XTcp* client = server.acceptClient();
                                        if(client->getSock()<=0) break;

                                        //新注册客户端事件
                                        ev.data.fd = client->getSock();
                                        ev.events=EPOLLIN|EPOLLET;
                                        epoll_ctl(epfd,EPOLL_CTL_ADD,client->getSock(),&ev);
                                        delete client;
                                }
                        }
                        else
                        {
                                cout<<"<<= data event"<<endl;
                                XTcp client;
                                client.setSock(event[i].data.fd);
                                client.receive(buf,1024);
                                client.sendData(msg,size);
                                //客户端处理完毕，清理事件
                                epoll_ctl(epfd,EPOLL_CTL_DEL,client.getSock(),&ev);
                                client.closeSocket();
                        }
                }
        }
}
