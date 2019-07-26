#include <iostream>
#include <thread>
#include <sys/syscall.h>
#include "EventLoop.h"
void threadFunc() {
    printf("threadFunc():pid = %d tid = %ld\n",getpid(),syscall(SYS_gettid));
    EventLoop loop;
    loop.loop();
}

int main()
{
    printf("main():pid = %d tid = %ld\n",getpid(),syscall(SYS_gettid));
    EventLoop loop;
    std::thread t(threadFunc);
    t.detach();
    loop.loop();
    pthread_exit(NULL);
    return 0;
}

