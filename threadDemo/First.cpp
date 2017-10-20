#include <iostream>
using namespace std;

//用户访问和获取线程变量。所有的线程都可以访问
pthread_key_t key;
void *run(void *ptr){
        int value=*(int *)ptr;
        int temp=1;
        //将temp的地址赋给key。
        pthread_setspecific (key, &temp);
        for(int i=0; i<3; i++) {
                //根据key获取对应的值
                int v=*(int *)pthread_getspecific(key);
                usleep(1000*100);
                cout<<"run key value>> "<<v<<endl<<flush;
        }
        return 0;
}
void *run2(void *ptr){
        int temp=2;
        pthread_setspecific (key, &temp);
        for(int i=0; i<3; i++) {
                int v=*(int *)pthread_getspecific(key);
                usleep(1000*150);
                cout<<"run2 key value>> "<<v<<endl<<flush;
        }
        return 0;
}

int main(){
        //创建key
        pthread_key_create(&key,NULL);
        int ret=0;
        int value=10;
        pthread_t id;
        pthread_attr_t attr;
        sched_param param;
        //初始化
        pthread_attr_init(&attr);
        //设置相关属性
        pthread_attr_setscope (&attr,PTHREAD_SCOPE_PROCESS);
        //获取线程优先级参数
        pthread_attr_getschedparam(&attr,&param);
        //设置优先级
        param.sched_priority=10;
        pthread_attr_setschedparam(&attr,&param);
        ret=pthread_create(&id,&attr,run,&value);
        if(ret) {
                cout<<"create thread failed "<<endl;
                return 0;
        }
        pthread_t id2;
        ret=pthread_create(&id2,NULL,run2,NULL);
        if(ret) {
                cout<<"create thread 2 failed "<<endl;
                return 0;
        }
        pthread_join(id,NULL);
        pthread_join(id2,NULL);
        pthread_key_delete(key);
        return 0;
}
