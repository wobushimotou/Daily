#pragma once
#include <algorithm>
#include <sys/eventfd.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <assert.h>
#include <vector>
#include <mutex>
#include <functional>
#include <poll.h>
#include <memory>
#include <pthread.h>
#include "./poll/epoll.h"
#include "Channel.h"
class epoll;
class Channel;
class EventLoop : public std::enable_shared_from_this<EventLoop>
{
public:
    typedef std::vector<Channel *>ChannelList;
    typedef std::function<void()> Functor;
    EventLoop();
    ~EventLoop();

    void loop();

    bool isInLoopThread() const { return threadId == syscall(SYS_gettid); }
    void updateChannel(Channel *channel);
    void removeChannel(Channel *channel);
    void quit();
    void runInLoop(const Functor &cb);
    void queueInLoop(const Functor &cb);
    pid_t threadId;

private:
    void handleRead();
    void doPendingFunctors();
    void wakeup();
    int createEventfd();

    ChannelList activeChanels;
    Channel *currentActiveChannel;

    bool looping;
    bool quit_;
    bool callingPendingFunctors;
    bool eventHanding;

    std::shared_ptr<epoll> poll_;

    int wakeupFd;
    std::shared_ptr<Channel> weakupChannel;
    std::mutex Mutex;
    std::vector<Functor > pendingFunctions;
};

