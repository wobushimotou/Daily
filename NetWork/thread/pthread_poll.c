#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <ctime>

void *f(void *arg) {
    int a = 0;
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid;
    time_t sum = 0; 
    time_t begin = clock();
    for(int i = 0;i < 1000;++i) {
        time_t pthread_begin = clock();
        pthread_create(&tid,NULL,f,NULL);
        time_t pthread_end = clock();
        sum += pthread_end - pthread_begin;
    }
    time_t end = clock();
    printf("time = %ld\n",end-begin);
    printf("invaildtime = %ld\n",sum);
    return 0;
}

