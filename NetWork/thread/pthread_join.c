#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int a;
void *f(void *arg) {
    printf("thread1 running\n");
    int *p = (int *)malloc(sizeof(int));
    *p = 111;
    a = 111;
    pthread_exit((void *)&a);
}

int main(int argc,char *argv[])
{
    pthread_t pid1;
    pthread_create(&pid1,NULL,f,NULL);
    
    int *p;
    pthread_join(pid1,(void **)&p);
    printf("线程结束的返回值为:%d\n",*p);
    return 0;
}

