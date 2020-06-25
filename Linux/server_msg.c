#include "msg.h"
int main()
{
    struct msg_queue msg;

    bzero(&msg,sizeof(msg));
    int msgid = msg_init();

    while(1) {
        int i = 0;
        i = msgrcv(msgid,&msg,sizeof(msg) - sizeof(long),1,0);
        printf("  %d\n",i);

        printf("  %s\n",msg.data);
    }

    msg.type = 1;




    return 0;
}

