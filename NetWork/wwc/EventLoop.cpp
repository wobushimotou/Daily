#include "EventLoop.h"

EventLoop::EventLoop()
    :threadId(syscall(SYS_gettid)),looping(false),poll_(std::make_shared<epoll>(this))
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
    quit_ = false;
    while(!quit_) {
        activeChanels.clear();
        poll_->poll(1000,&activeChanels);
        for(auto p = activeChanels.begin();p != activeChanels.end();++p) {
            (*p)->handleEvent();
        }
    }
    LOG_DEBUG << "EventLoop stop looping\n";
    looping = false;
}


void EventLoop::updateChannel(Channel *channel)
{
    std::cout << "EventLoop updateChannel()\n";
    poll_->updateChannel(channel);
}

void EventLoop::quit()
{
    quit_ = true;
}

