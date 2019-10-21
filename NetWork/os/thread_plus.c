/*
 *  实验三改进代码
 *
 *
 * */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>



pthread_mutex_t mutex;
#define MAX_THREAD 3 //线程个数
unsigned long long main_counter,counter[MAX_THREAD];

void *thread_worker(void *);
int main(int argc,char *argv[])
{
    pthread_mutex_init(&mutex,NULL);
    int i,rtn,ch;
    pthread_t pthread_id[MAX_THREAD] = {0}; //存放线程id
    int t[MAX_THREAD];
    for(i = 0;i < MAX_THREAD;++i) {
        t[i] = i;
        pthread_create(&pthread_id[i],NULL,thread_worker,(void *)&t[i]);
    }
    do{
        unsigned long long sum = 0;

        
        pthread_mutex_lock(&mutex);
        for(i = 0;i < MAX_THREAD;++i) {
            sum += counter[i];
            printf("%llu ",counter[i]);
        }

        printf("  %llu/%llu",main_counter,sum);
        pthread_mutex_unlock(&mutex);

    }while((ch = getchar()) != 'q');
    return 0;
}


void *thread_worker(void *p) {
    int thread_num;
    thread_num = *(int *)p;
    while(1) {
        pthread_mutex_lock(&mutex);
        counter[thread_num]++;
        main_counter++;
        pthread_mutex_unlock(&mutex);
    }

}
