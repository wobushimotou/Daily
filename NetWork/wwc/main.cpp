#include <iostream>
#include <thread>
#include "./log/log.h"
#include "EventLoop.h"
int f(EventLoop *loop) {
    loop->loop();
    return 0;
}

int main()
{
    EventLoop loop;
    std::thread t(f,&loop);
    t.join();
    return 0;
}

