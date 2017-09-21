#include <iostream>
using namespace std;
class XThread {
private:
XTcp* sock;
public:
XThread(XTcp* sock){
        this->sock=sock;
}
~XThread(){
        cout<<"release"<<endl;
}
void run(){
        int n=0;
        cout<<"new thread for socket "<<this->sock->getSock()<<endl;
        char buff[1024];
        for(;; ) {
                n = sock->receive(buff,1024);
                if(n<=0) {
                        //如果客户端断开了，这里就跳出循环
                        break;
                }
                buff[n] = '\0';
                printf("%d=>%s",n,buff);
        }
        sock->closeSocket();
}
};
