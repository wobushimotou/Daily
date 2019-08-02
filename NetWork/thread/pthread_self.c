#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

void *f(void *arg) {
    if(*(int *)arg)
        printf("父进程所属线程ID为%ld\n",pthread_self());
    else
        printf("子进程所属线程ID为%ld\n",pthread_self());

    pthread_exit(NULL);
}
int main()
{
    pid_t pid1;
    pthread_t tid1;
    pthread_t tid2;
    int a;
    pid1 = fork();
    if(pid1 == 0) {
        printf("子进程主线程ID为%ld\n",pthread_self());
        a = 0;
        pthread_create(&tid1,NULL,f,(void *)&a);
        pthread_join(tid1,NULL);
    }
    else {
        printf("父进程主线程ID为%ld\n",pthread_self());
        a = 1;
        pthread_create(&tid2,NULL,f,(void *)&a);
        pthread_join(tid2,NULL);
    }
    return 0;
}

