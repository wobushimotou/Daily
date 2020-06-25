#include "sem.h"
int main()
{
    key_t key = 66;
    sem_id = semget(key,1,IPC_CREAT);

    int fd = open("./1.txt",O_RDWR);
    char data[100];



    //get sem
    while(semaphore_p()) {
        bzero(data,100);
        read(fd,data,100);
        printf("%s\n",data);

        semaphore_v();
    }

    close(fd);


    return 0;
}

