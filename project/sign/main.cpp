#include <iostream>
#include "MacGet.h"
int main()
{
    string dst;
    MacGet Send;
    MacGet Recv;

    for(int i = 1;i < 255;++i) {
        dst = "192.168.3."+to_string(i);
        Send = dst;
        Send.arpSend();
    }
    while(1) {
        Recv.arpRecv();
    }
    return 0;
}

