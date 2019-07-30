#include "EventLoop.h"

EventLoop::EventLoop()
    :threadId(syscall(SYS_gettid)),looping(false)
{
    LOG_DEBUG << "EventLoop Created\n";
}


EventLoop::~EventLoop()
{
    if(looping)
        LOG_DEBUG << "running,closing error\n";
}
void EventLoop::loop()
{
    if(!isInLoopThread()) {
        LOG_DEBUG << "not in LoopThread Exit\n";
        LOG_DEBUG.~log();
        exit(0);
    }

    looping = true;
    ::poll(NULL,0,1000);
    LOG_DEBUG << "EventLoop stop looping\n";
    looping  = false;
}


