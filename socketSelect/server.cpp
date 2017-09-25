#include <iostream>
#include <stdlib.h>
using namespace std;
#include "XTcp.h"
int main(int argc,char ** argv){
        unsigned short port=8888;
        if(argc>1) {
                port=atoi(argv[1]);
        }
        XTcp xtcp;
        xtcp.createSocket();
        xtcp.bindPort(port);
        xtcp.listenSocket();
        while (true) {
                /* code */
                xtcp.acceptClient();
        }
}
