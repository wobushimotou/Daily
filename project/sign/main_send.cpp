#include <iostream>
#include "MacGet.h"
#include <thread>

string dst_mac;
void Recv(void) {
    MacGet mc;
    int flag = 1;
    while(1) {
        if(flag) {
            dst_mac = mc.arpRecv();
            flag = 0;
    
        }
        else
            mc.arpRecv();
    }
}
int main()
{    
    string dst = "192.168.3.47";

    thread t(Recv);
    t.detach();

    //得到路由器mac地址
    for(int i = 1;i < 255;++i) {
        dst = "192.168.3."+to_string(i);
        MacGet mc(dst);
        mc.arpSend();
    }
    return 0;
}

