#include "sem.h"
int main()
{
    key_t key = 66;
    sem_id = semget(key,1,IPC_CREAT | 0666);

    set_semvalue();

    int fd = open("./1.txt",O_RDWR);
    char data[100];

    //get sem
    while(semaphore_p()) {
        bzero(data,100);
        scanf("%s",data);
        write(fd,data,100);

        lseek(fd,0,SEEK_SET);
        semaphore_v();
    }

    close(fd);
    return 0;
}

