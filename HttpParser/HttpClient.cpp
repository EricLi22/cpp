#include "HttpClient.h"
#include "string.h"
#include "thread"
// #include <regex>
#include "Response.h"
#include <stdlib.h>
#include <boost/regex.hpp>
#include "Request.h"
#include "http_parser.h"

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

int on_url(http_parser* _, const char* at, size_t length) {
        (void)_;
        printf("Url: %.*s\n", (int)length, at);
        return 0;
}
int on_header_field(http_parser* _, const char* at, size_t length) {
        (void)_;
        printf("Header field: %.*s\n", (int)length, at);
        return 0;
}

int on_header_value(http_parser* _, const char* at, size_t length) {
        (void)_;
        printf("Header value: %.*s\n", (int)length, at);
        return 0;
}
int on_message_begin(http_parser* _) {
        (void)_;
        printf("\n***MESSAGE BEGIN***\n\n");
        return 0;
}

int on_headers_complete(http_parser* _) {
        (void)_;
        printf("\n***HEADERS COMPLETE***\n\n");
        return 0;
}

int on_message_complete(http_parser* _) {
        (void)_;
        printf("\n***MESSAGE COMPLETE***\n\n");
        return 0;
}
int on_body(http_parser* _, const char* at, size_t length) {
        (void)_;
        printf("Body: %.*s\n", (int)length, at);
        return 0;
}


void HttpClient::run(){
        char buf[1024]={0};
        //读取客户度发来的数据
        int length=client->receive(buf,sizeof(buf)-1);
        if(length<=0) {
                client->closeSocket();
        }else{

                /***********解析请求数据************/
                http_parser_settings settings;
                settings.on_url = on_url;
                settings.on_header_field = on_header_field;
                settings.on_header_value = on_header_value;
                settings.on_message_begin = on_message_begin;
                settings.on_status = 0;
                settings.on_body = on_body;
                settings.on_headers_complete = on_headers_complete;
                settings.on_message_complete = on_message_complete;

                http_parser *parser =(http_parser * )malloc(sizeof(http_parser));
                http_parser_init(parser, HTTP_REQUEST);
                // parser->data = client->getSock();
                size_t nparsed;
                nparsed=http_parser_execute(parser, &settings, buf, length);
                if (parser->upgrade) {
                        /* handle new protocol */
                        cout<<"handle new protoco"<<endl;
                } else if (nparsed != length) {
                        /* Handle error. Usually just close the connection. */
                        cout<<"Handle error"<<endl;
                }else{
                        cout<<"Handle success !"<<endl;
                }
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
                        string path="/code/http/www";
                        if(req.getPath()=="/") {
                                path.append("/index.html");
                        }else{
                                path.append(req.getPath());
                        }
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
                                cout<<"file not exist"<<endl;
                        }
                        resp.setContentLength(fileSize);
                        resp.addHead("Content-Type","text/html");
                        resp.addHead("Server","eric http");
                        string headsStr=resp.getData();
                        client->sendData(headsStr.c_str(),headsStr.size());
                        if(file!=NULL) {
                                char dataBuf[1024*100]={0};
                                while(true) {
                                        int len= fread(dataBuf,1,sizeof(dataBuf),file);
                                        if(len<=0) {
                                                break;
                                        }
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
