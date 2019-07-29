#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int a;
void *f(void *arg) {
    for(int i = 0;i < 10000;++i)
        ++a;
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,f,NULL);
    pthread_create(&tid2,NULL,f,NULL);

    usleep(10);
    printf("%d\n",a);
    return 0;
}

