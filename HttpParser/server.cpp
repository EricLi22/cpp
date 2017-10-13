#include <iostream>
#include <stdlib.h>
#include "HttpServer.h"
using namespace std;
int main(int argc,char ** argv){
        unsigned short port=8888;
        if(argc>1) {
                port=atoi(argv[1]);
        }
        HttpServer HttpServer;
        if(!HttpServer.start(port)){
              cout<<"start http failed!"<<endl;
        }
        getchar();
}
