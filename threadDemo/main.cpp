#include <iostream>
using namespace std;
void *thread(void *ptr)
{
        int index=*((int *)ptr);
        for(int i = 0; i < 3; i++) {
                cout <<index<< endl;
        }
        return 0;
}

void freeWinKey (){

}
int main(){
        int ret =0;
        int index=10;
        pthread_attr_t attr;
        sched_param param;
        pthread_attr_init(&attr);
        pthread_attr_getschedparam(&attr,&param);
        param.sched_priority=1;
        pthread_attr_setschedparam(&attr,&param);
        pthread_t id;
        ret = pthread_create(&id, &attr, thread, &index);
        if(ret) {
                cout << "Create pthread error!" << endl;
                return 1;
        }
        pthread_join(id, NULL);
        return 0;
}
