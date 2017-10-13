#include <iostream>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
using namespace std;
#define BUFF_LEN 1024
int main(){
        int sock=socket(AF_INET,SOCK_DGRAM,0);
        int ret=0;
        sockaddr_in addr;
        addr.sin_family=AF_INET;
        //INADDR_ANY为本地Ip
        addr.sin_addr.s_addr=htonl(INADDR_ANY);
        addr.sin_port=8888;

        char buf[BUFF_LEN]={0};
        int recvRet;
        //0表示对方关闭，-1为发生错误。
        while (true) {
                //标准输入，会带上'\n'
                fgets(buf,BUFF_LEN,stdin);
                if(string(buf)=="exit\n") {
                        break;
                }else{
                        recvRet=sendto(sock,buf,strlen(buf),NULL,(sockaddr *)&addr,sizeof(addr));
                        if(recvRet<=0) {
                                cout<<"receive failed"<<endl;
                        }
                }
        }
        if(sock>0) {
                close(sock);
                sock=-1;
        }
        return 0;
}
