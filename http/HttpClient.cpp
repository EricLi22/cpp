#include "HttpClient.h"
#include "string.h"
#include "thread"

HttpClient::HttpClient(XTcp* client){
        this->client=client;
}
HttpClient::~HttpClient(){
        if(client!=NULL) {
                client->closeSocket();
                delete client;
                client=NULL;
        }
}

void HttpClient::run(){

        //接受输入
        char buf[1024]={0};
        int length=client->receive(buf,sizeof(buf)-1);
        if(length<=0) {
                client->closeSocket();
        }else{
                cout<<">>> "<<buf<<endl;
                string firstLine="HTTP/1.1 200 OK\r\n";
                string heads="Content-Length: ";
                string content="Success!";
                heads+=content.size();
                heads+="\r\n\r\n";

                string res=firstLine;
                res+=heads;
                res+=content;
                cout<<res.c_str()<<endl;
                int size = strlen(res.c_str());
                client->sendData(res.c_str(),size);
                client->closeSocket();
        }
}
bool HttpClient::process(){
        thread t(&HttpClient::run,this);
        t.detach();
}
