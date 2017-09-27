#include "Response.h"
Response::Response(){
        code=200;
        protocol="HTTP/1.1";
        msg="OK";
}
Response::~Response(){

}
void Response::setCode(int code){
        this->code=code;
}
void Response::setMsg(const char* msg){
        this->msg=msg;
}
void Response::setProtocol(const char protocol){
        this->protocol=protocol;
}
void Response::addHead( string key,string value){
        pair<string,string> p(key,value);
        headers.insert(p);
}
void Response::setContentLength(int length){
        char lenBuf[10]={0};
        sprintf(lenBuf,"%d",length);
        addHead("Content-Length",lenBuf);
}
string Response::getData() {
        string result;
        char codeBuf[4];
        sprintf(codeBuf,"%d",code);
        result.append(protocol).append(" ").append(codeBuf).append(" ").append(msg).append("\r\n");
        for(map<string,string>::iterator it=headers.begin(); it!=headers.end(); it++) {
                result.append(it->first).append(": ").append(it->second).append("\r\n");
        }
        result.append("\r\n");
        return result;
}
