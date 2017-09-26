#include "HttpServer.h"
#include "thread"
#include <sys/epoll.h>
#include <string.h>

HttpServer::HttpServer(){
        this->server=NULL;
        exit=false;
}

HttpServer::~HttpServer(){
        if(this->server!=NULL) {
                this->server->closeSocket();
                delete this->server;
        }
}

void HttpServer::run(){
        cout<<"run ..."<<endl;
        this->server->listenSocket();
        int epfd = epoll_create(256);
        //注册epoll事件
        struct epoll_event ev;
        ev.data.fd = server->getSock();
        //数据接入事件|边缘检测,ET模式仅当状态发生变化的时候才获得通知
        ev.events=EPOLLIN|EPOLLET;
        epoll_ctl(epfd,EPOLL_CTL_ADD,server->getSock(),&ev);
        struct epoll_event event[20];
        server->SetBlock(false);


        char buf[1024] = {0};
        const char *msg = "HTTP/1.1 200 OK\r\nContent-Length: 1\r\n\r\nX";
        int size = strlen(msg);
        while (!exit) {
                int count = epoll_wait(epfd,event,20,500);
                if(count <=0) continue;
                for(int i=0; i<count; i++) {
                        //连接事件发生
                        if(event[i].data.fd == server->getSock())
                        {
                                cout<<"<<= connect event"<<endl;
                                for(;; )
                                {
                                        XTcp* client = server->acceptClient();
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
        cout<<"server exit"<<endl;
        server->SetBlock(true);
}

bool HttpServer::start(unsigned short port){
        this->server=new XTcp;
        this->server->createSocket();
        if(server->bindPort(port)<0) {
                return false;
        }
        thread t(&HttpServer::run,this);
        t.detach();
        return true;
}
void HttpServer::setExit(bool exit){
        this->exit=exit;
}
