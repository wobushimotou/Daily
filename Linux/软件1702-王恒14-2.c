#pragma once
//头文件
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>


union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int sem_id;
int set_semvalue()
{
    union semun sem_union;
    sem_union.val = 1;
    if(semctl(sem_id,0,SETVAL,sem_union)==-1)
        return 0;
    return 1;
}

int semaphore_p()
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = -1;
    sem_b.sem_flg = SEM_UNDO;
    if(semop(sem_id,&sem_b,1)==-1)
    {
        fprintf(stderr,"semaphore_p failed\n");
        return 0;
    }
    return 1;
}

int semaphore_v()
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = 1;
    sem_b.sem_flg = SEM_UNDO;
    if(semop(sem_id,&sem_b,1)==-1)
    {
        fprintf(stderr,"semaphore_v failed\n");
        return 0;
    }
    return 1;
}


//client
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

//server
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

