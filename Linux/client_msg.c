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

