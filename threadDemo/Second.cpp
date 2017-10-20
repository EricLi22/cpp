#include <iostream>
using namespace std;
char buffer;
int buffer_has_item=0;
pthread_mutex_t mutex;
void writerFunc(){
        while(1) {
                /* 锁定互斥锁*/
                pthread_mutex_lock (&mutex);
                buffer_has_item++;
                cout<<"write "<<buffer_has_item<<endl;
                /* 打开互斥锁*/
                pthread_mutex_unlock(&mutex);
                usleep(1000*200);
        }
}
void *readerFunc(void *ptr){
        while(1) {
                pthread_mutex_lock(&mutex);
                if(buffer_has_item>0) {
                        cout<<"read >>>> "<<buffer_has_item<<endl;
                        buffer_has_item--;
                }
                pthread_mutex_unlock(&mutex);
                usleep(1000*500);
        }
}
int main(){
        pthread_t id;
        pthread_mutex_init (&mutex,NULL);
        pthread_create(&id, NULL,readerFunc, NULL);
        writerFunc();
        return 0;
}
