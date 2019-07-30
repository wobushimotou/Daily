#pragma once
#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "./log/log.h"
#include "./poll/epoll.h"
#include <poll.h>
#include <assert.h>
#include "Channel.h"
class EventLoop
{
public:
    EventLoop();
    ~EventLoop();

    void loop();

    bool isInLoopThread() const { return threadId == syscall(SYS_gettid); }
    void updateChannel(Channel *channel);
private:
    pid_t threadId;
    bool looping;
    log LOG_DEBUG;
};

