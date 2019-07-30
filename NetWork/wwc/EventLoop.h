#pragma once
#include <poll.h>
#include <memory>
#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "./log/log.h"
#include "./poll/epoll.h"
#include <assert.h>
#include "Channel.h"
class epoll;
class EventLoop
{
public:
    typedef std::vector<Channel *>ChannelList;
    EventLoop();
    ~EventLoop();

    void loop();

    bool isInLoopThread() const { return threadId == syscall(SYS_gettid); }
    void updateChannel(Channel *channel);
    void quit();
private:

    ChannelList activeChanels;
    Channel *currentActiveChannel;

    pid_t threadId;
    bool looping;
    bool quit_;
    log LOG_DEBUG;
    std::shared_ptr<epoll> poll_;
};

