#include <iostream>
#include <semaphore.h>
#include <string.h>
#include <stdio.h>
using namespace std;
//信号量
sem_t sem;
void * run(void *ptr){
        char *buf=(char *)ptr;
        while(strcmp("exit\n",buf)!=0) {
                //新号量-1
                sem_wait(&sem);
                cout<<"thread output>> "<<buf<<endl<<flush;
        }
        return 0;
}

int main(){
        char buf[100]={0};
        int ret=0;
        pthread_t id;
        //初始化信号量数量为2。默认类型，非0位进程间共享
        ret=sem_init(&sem, 0, 2);
        if(ret) {
                cout<<"sem_init failed"<<endl;
        }
        pthread_create(&id,NULL,run,buf);
        //循环从标准输入读（fgets会将\n也读入）
        while(fgets(buf,sizeof(buf),stdin)) {
                if(strcmp("exit\n",buf)==0) {
                        break;
                }
                //信号量+1
                sem_post(&sem);
        }
        //清理信号量
        sem_destroy(&sem);
        return 0;
}
