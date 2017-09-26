#include "HttpClient.h"
#include "string.h"
#include "thread"

HttpClient::HttpClient(){
        client=NULL;
}
HttpClient::~HttpClient(){
        if(client!=NULL) {
                client->closeSocket();
                delete client;
                client=NULL;
        }
}

void HttpClient::run(){
        const char *msg = "HTTP/1.1 200 OK\r\nContent-Length: 1\r\n\r\nX";
        int size = strlen(msg);

        char buf[1024]={0};
        int length=client->receive(buf,sizeof(buf)-1);
        if(length<=0) {
                client->closeSocket();
        }else{
                cout<<">>> "<<buf<<endl;
                client->sendData(msg,strlen(msg));
                client->closeSocket();
        }
}
bool HttpClient::process(){
    thread t(&HttpClient::run,this);
    t.detach();
}
