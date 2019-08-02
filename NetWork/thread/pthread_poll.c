#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <ctime>

void *f(void *arg) {
    pthread_exit(NULL);
}

int main()
{
    time_t sum = 0; 
    time_t begin = clock();
    pthread_t pthreads[1000];
    for(int i = 0;i < 1000;++i) {
        time_t pthread_begin = clock();
        pthread_create(&pthreads[i],NULL,f,NULL);
        time_t pthread_end = clock();
        sum += pthread_end - pthread_begin;
    }
    for(int i = 0;i < 1000;++i) {
        pthread_join(pthreads[i],NULL);
    }
    time_t end = clock();
    printf("time = %ld\n",end-begin);
    printf("invaildtime = %ld\n",sum);
    return 0;
}

