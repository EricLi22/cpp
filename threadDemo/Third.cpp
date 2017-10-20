#include <iostream>
using namespace std;
int buffer_has_item=0;
pthread_mutex_t mutex;
pthread_cond_t count_nonzero;
void writerFunc(){
        while(1) {
                pthread_mutex_lock (&mutex);
                buffer_has_item+=2;
                cout<<"write "<<buffer_has_item<<endl;
                pthread_mutex_unlock(&mutex);
                //激活阻塞的读线程
                pthread_cond_signal(&count_nonzero);
                usleep(1000*200);
        }
}
void *readerFunc(void *ptr){
        while(1) {
                pthread_mutex_lock(&mutex);
                if(buffer_has_item<=0) {
                        //暂时解锁，把资源让出，等待写线程写入。
                        //被激活后会自动加锁
                        pthread_cond_wait( &count_nonzero, &mutex);
                }
                cout<<"read >>>> "<<buffer_has_item<<endl;
                buffer_has_item--;
                pthread_mutex_unlock(&mutex);
        }
}
int main(){
        pthread_t id;
        pthread_mutex_init (&mutex,NULL);
        pthread_create(&id, NULL,readerFunc, NULL);
        writerFunc();
        return 0;
}
