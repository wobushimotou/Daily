#include <pthread.h>
#include <unistd.h>
int n[2] = {0};
void *Add(void *a) {
    int num = *(int *)a;
    while(1) {
        n[num]++;
        sleep(1);
    }
}
int main()
{

    pthread_t a;
    pthread_t b;
    int _a = 0;
    int _b = 1;
    pthread_create(&a,NULL,Add,(void *)&_a);
    pthread_create(&b,NULL,Add,(void *)&_b);

    return 0;
}

