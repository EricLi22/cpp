#include <iostream>
using namespace std;

class SocketThread{
private:
  int sock;
public:
    SocketThread(int sock){
        this->sock=sock;
    }
    void Main(){
        cout<<"new thread "<<endl;
    }
};
