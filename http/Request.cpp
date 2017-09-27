#include "Request.h"
#include <boost/regex.hpp>
Request::Request(){

}
Request::~Request(){

}
void Request::setBody(string body){
        this->body=body;
}
bool Request::parse(){
        if(body.empty()) {
                return false;
        }
        boost::regex reg("^(\\w+) /(\\w*([.]\\w+)?) HTTP/1");
        boost::smatch sm;
        regex_search(body,sm,reg);
        if(sm.size()==0) {
                return false;
        }else{
                cout<<"Regex =>"<<sm[1]<<"|"<<sm[2]<<"|"<<sm[3]<<endl;
                method=sm[1];
                path.clear();
                path.append("/").append(sm[2]);
                postfix=sm[3];
        }
        return true;
}
string Request::getPostfix(){
        return postfix;
}
string Request::getMethod(){
        return method;
}
string Request::getPath(){
        return path;
}
string Request::getProtocol(){
        return protocol;
}
string Request::getContent(){
        return content;
}
map<string,string> Request::getParam(){

}
map<string,string> Request::getHeaders(){

}
