#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
pthread_mutex_t rmutex;
pthread_mutex_t wmutex;
int readcount = 0;
char buf[100] = {'0'};

void *r(void *re) {
    while(1) {
        pthread_mutex_lock(&rmutex);
        if(readcount == 0)
            pthread_mutex_lock(&wmutex);
        readcount++;
        pthread_mutex_unlock(&rmutex);
        
        printf("%s\n",buf);
        pthread_mutex_lock(&rmutex);
        readcount--;
        if(readcount == 0)
            pthread_mutex_unlock(&wmutex);
        pthread_mutex_unlock(&rmutex);
    }
    pthread_exit(NULL);
}

void *w(void *we) {
    while(1) {
            pthread_mutex_lock(&wmutex);
            buf[0] = 'w';
            pthread_mutex_unlock(&wmutex);
    }
    pthread_exit(NULL);
}

int main()
{

    pthread_t R;
    pthread_t W;
    pthread_create(&R,NULL,r,NULL);
    pthread_create(&W,NULL,w,NULL);

    sleep(10);
    return 0;
}

