#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *f(void *arg) {
    pthread_mutex_t *mutex = (pthread_mutex_t *)arg;
    pthread_mutex_lock(mutex);
    sleep(10);
    pthread_mutex_unlock(mutex);
    pthread_exit(NULL);
}

int main()
{
    pthread_mutex_t mutex;
    pthread_t tid;
    pthread_mutex_init(&mutex,NULL);

    pthread_create(&tid,NULL,f,(void *)&mutex);
    sleep(1);

    pthread_mutex_lock(&mutex);

    if(pthread_mutex_destroy(&mutex) == EBUSY)
        printf("销毁错误\n");
    pthread_mutex_unlock(&mutex);


    return 0;
}

