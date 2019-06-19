#include <iostream>
#include "MacGet.h"

int main()
{
    string dst = "192.168.43.133";
    MacGet mc(dst);
    mc.arpSend();
    mc.arpRecv();
    return 0;
}

