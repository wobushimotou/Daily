#pragma once
#include <boost/noncopyable.hpp>
#include <sys/syscall.h>
#include <iostream>
#include <assert.h>
#include <poll.h>

class EventLoop:boost::noncopyable
{
public:
    EventLoop();
    ~EventLoop();

    //运行事件循环
    void loop();
    
    void assertInLoopThread() {
        if(!isInLoopThread()) {
            exit(0);
        }
    }

    EventLoop* getEventLoopOfCurrentThread();
    bool isInLoopThread() const { return threadId_ == syscall(SYS_gettid);  }
    pid_t gettid() { return threadId_; }
private:

    bool looping_;
    const pid_t threadId_;
};

