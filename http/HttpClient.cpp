#include "HttpClient.h"
#include "string.h"
#include "thread"
// #include <regex>
#include "Response.h"
#include <stdlib.h>
#include <boost/regex.hpp>

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
        char buf[1024]={0};
        cout<<"run"<<endl;
        //读取客户度发来的数据
        int length=client->receive(buf,sizeof(buf)-1);
        if(length<=0) {
                client->closeSocket();
        }else{
                cout<<"\n\n>>> "<<buf<<endl;
                Response resp;
                string souStr=buf;
                boost::regex reg("^(\\w+) /(\\w*([.]\\w+)?) HTTP/1");
                boost::smatch sm;
                regex_search(souStr,sm,reg);
                if(sm.size()==0) {
                        resp.setCode(404);
                        resp.setMsg("protocol first line error");
                        string headsStr=resp.getData();
                        client->sendData(headsStr.c_str(),headsStr.size());
                }else{
                        string content="success";
                        char lenBuf[10]={0};
                        sprintf(lenBuf,"%d", content.size());
                        resp.addHead(string("Content-Length: "),string(lenBuf));
                        cout<<lenBuf<<endl;
                        string headsStr=resp.getData();
                        cout<<headsStr.c_str();
                        cout<<content.c_str()<<endl;
                        client->sendData(headsStr.c_str(),headsStr.size());
                        client->sendData(content.c_str(),content.size());
                }
                client->closeSocket();
        }
}
bool HttpClient::process(){
        //开启线程进行业务处理
        thread t(&HttpClient::run,this);
        t.detach();
}
