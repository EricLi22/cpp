#include "HttpClient.h"
#include "string.h"
#include "thread"
// #include <regex>
#include "Response.h"
#include <stdlib.h>
#include <boost/regex.hpp>
#include "Request.h"

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
        //读取客户度发来的数据
        int length=client->receive(buf,sizeof(buf)-1);
        if(length<=0) {
                client->closeSocket();
        }else{
                cout<<"\n\n>>> "<<buf<<endl;
                Request req;
                Response resp;
                req.setBody(string(buf));
                if(!req.parse()) {
                        cout<<"parse failed"<<endl;
                        resp.setCode(404);
                        resp.setMsg("protocol first line error");
                        string headsStr=resp.getData();
                        client->sendData(headsStr.c_str(),headsStr.size());

                }else{
                        cout<<req.getPath()<<endl;
                        string path="/code/http/www";
                        if(req.getPath()=="/") {
                                path.append("/index.html");
                        }else{
                                path.append(req.getPath());
                        }
                        cout<<"Path =>"<<path<<endl;
                        //解析Php文件
                        if(req.getPostfix()==".php") {
                                string cmd="php-cgi ";
                                string resFilePath;
                                resFilePath.append(path).append(".html");
                                cmd.append(path).append(" > ").append(resFilePath);
                                cout<<cmd<<endl;
                                system(cmd.c_str());
                                path=resFilePath;
                        }
                        //读写文件
                        int fileSize=0;
                        FILE *file=fopen(path.c_str(),"r");
                        if(file!=NULL) {
                                fseek(file,0L,SEEK_END);
                                //获取文件大小
                                fileSize=ftell(file);
                                fseek(file,0L,SEEK_SET);
                        }else{
                                cout<<"file read error"<<endl;
                        }
                        resp.setContentLength(fileSize);
                        // if(sm[3].str().empty()) {
                        resp.addHead("Content-Type","text/html");
                        // }else{
                        //         resp.addHead("Content-Type","image/jpeg");
                        // }
                        resp.addHead("Server","eric http");
                        string headsStr=resp.getData();
                        cout<<"<<< "<<headsStr.c_str();
                        client->sendData(headsStr.c_str(),headsStr.size());
                        if(file!=NULL) {
                                char dataBuf[1024*100]={0};
                                while(true) {
                                        int len= fread(dataBuf,1,sizeof(dataBuf),file);
                                        if(len<=0) {
                                                break;
                                        }
                                        cout<<"===>send Data "<<len<<endl;
                                        client->sendData(dataBuf,len);
                                }

                                fclose(file);
                        }
                }
                client->closeSocket();
        }
}
bool HttpClient::process(){
        //开启线程进行业务处理
        thread t(&HttpClient::run,this);
        t.detach();
}
