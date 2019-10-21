/*
 *  实验四代码
 *
 * */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>

#define LOOP_TIMES 10000

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

void *thread_worker(void *);
void critical_section(int thread_num,int i);
int main(int argc,char *argv[])
{
    pthread_mutex_init(&mutex1,NULL);
    pthread_mutex_init(&mutex2,NULL);

    int i,rtn;
    pthread_t pthread_id = 0;
    rtn = pthread_create(&pthread_id,NULL,thread_worker,NULL);
    if(rtn != 0) {
        printf("create thread ERROR!\n");
        return -1;
    }
    for(i = 0;i != LOOP_TIMES;++i) {
        pthread_mutex_lock(&mutex1);
        printf("Main Get Mutex1 Wait for Mutex2\n");
        pthread_mutex_lock(&mutex2);
        printf("Main Get Mutex2\n");
        critical_section(1,i);
        pthread_mutex_unlock(&mutex2);
        pthread_mutex_unlock(&mutex1);
    }

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
    
    return 0;
}


void *thread_worker(void *p) {
    for(int i = 0;i != LOOP_TIMES;++i) {
        pthread_mutex_lock(&mutex2);
        printf("Thread Get Mutex2 Wait for Mutex1\n");
        pthread_mutex_lock(&mutex1);
        printf("Thread Get Mutex1\n");
        critical_section(2,i);
        pthread_mutex_unlock(&mutex1);
        pthread_mutex_unlock(&mutex1);
    }
}

void critical_section(int thread_num,int i) {
    printf("Thread:%d:%d\n",thread_num,i);
}
