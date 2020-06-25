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
