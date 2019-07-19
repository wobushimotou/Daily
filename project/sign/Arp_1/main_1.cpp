#include <iostream>
#include <hiredis/hiredis.h>
#include "Arp_1.h"
#include <thread>
#include <fstream>
#include <vector>

vector<string> vec;

void Recv(void) {
    Arp mc;
    string result;
    while(1) {
        result = mc.arpRecv();
        if(result != "wh")
            vec.push_back(result);
    }
}

int main()
{    
    string dst;

    thread t(Recv);
    t.detach();

    //得到路由器mac地址
    for(int i = 1;i < 255;++i) {
        dst = "192.168.3."+to_string(i);
        Arp mc(dst);
        mc.arpSend();
    }

    for(auto p = vec.begin();p != vec.end();++p) {
       for(size_t i = 0;i < p->length();++i) {
            unsigned char q = p->at(i);
            int m = q;
            cout.width(2);
            cout.fill('0');
            cout << hex << m << ":";
        }
        cout << endl;
    }
    cout << "size=" << vec.size() << endl;
    return 0;
}

