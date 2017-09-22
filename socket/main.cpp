#include <iostream>
using namespace std;
#include "XTcp.h"
int main(int argc,char **argv){
        unsigned short port=8888;
        if(argc>2) {
                char *portStr=argv[1];
                port=atoi(portStr);
        }
        XTcp server;
        server.createSocket();
        server.bindPort(port);
        server.listenSocket();
        while (true) {
                /* code */
                XTcp* client=server.acceptClient();
        }
        return 0;
}
