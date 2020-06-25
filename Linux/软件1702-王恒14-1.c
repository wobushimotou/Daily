//头文件
#pragma once
#include <sys/types.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define FILEPATH "/tmp"
#define PROJID 66
struct msg_queue{
    long type;
    char data[100];
};

int msg_init() {
    int msgid;
    key_t key;

    key = ftok(FILEPATH, PROJID);
    if (key == -1) {
        exit(1);
    }

    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        exit(1);
    }
    return msgid;
}

//client
#include "msg.h"
int main()
{

    int msgid = msg_init();

    struct msg_queue msg;
    
    while(1) {
        bzero(&msg,sizeof(msg));
        scanf("%s",msg.data);
        msg.type = 1;
        msgsnd(msgid, (void *)&msg, sizeof(msg) - sizeof(long), 0);
    }

    return 0;
}

//server
#include "msg.h"
int main()
{
    struct msg_queue msg;

    bzero(&msg,sizeof(msg));
    int msgid = msg_init();

    while(1) {
        int i = 0;
        i = msgrcv(msgid,&msg,sizeof(msg) - sizeof(long),1,0);
        printf("%d\n",i);

        printf("%s\n",msg.data);
    }

    msg.type = 1;




    return 0;
}

