#include "EventLoop.h"
__thread EventLoop* t_loopInThisThread = 0;
EventLoop::EventLoop() 
    :looping_(false),
    threadId_(syscall(SYS_gettid))
{
    std::cout << "EventLoop created" << this << "in thread " << threadId_; 
    if(t_loopInThisThread) {
        std::cout << "Another EventLoop" << t_loopInThisThread << "exist in this thread" << threadId_;
    }
    else {     
        t_loopInThisThread = this;
    }
}

EventLoop::~EventLoop() {
    assert(!looping_); 
    t_loopInThisThread = NULL;
}

EventLoop *EventLoop::getEventLoopOfCurrentThread() {
    return t_loopInThisThread;
}

void EventLoop::loop() {
    assert(!looping_);
    assertInLoopThread();
    looping_ = true;

    ::poll(NULL,0,5*100);
    std::cout << "EventLoop" << this << "stop looping";
    looping_ = false;
}
