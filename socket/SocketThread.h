#ifndef SOCKET_THREAD_H
#define SOCKET_THREAD_H
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>

using namespace std;
class SocketThread{
private:
  int sock;
public:
    SocketThread(int sock){
        this->sock=sock;
    }
    ~SocketThread(){
      cout<<"release"<<endl;
    }
    void run(){
        int n=0;
        cout<<"new thread for socket "<<this->sock<<endl;
        char buff[1024];
        for(;; ) {
                n = recv(this->sock,buff,1024,0);
                if(n<=0) {
                        //如果客户端断开了，这里就跳出循环
                        break;
                }
                buff[n] = '\0';
                printf("%d=>%s",n,buff);
        }
        close(this->sock);
        cout<<this->sock<<" closed"<<endl;
    }
};
#endif
