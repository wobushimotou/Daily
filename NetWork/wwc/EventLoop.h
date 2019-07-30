#pragma once
#include <sys/eventfd.h>
#include <mutex>
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
    typedef std::function<void()> Functor;
    EventLoop();
    ~EventLoop();

    void loop();

    bool isInLoopThread() const { return threadId == syscall(SYS_gettid); }
    void updateChannel(Channel *channel);
    void quit();
    void runInLoop(const Functor &cb);
private:
    void queueInLoop(const Functor &cb);
    void handleRead();
    void doPendingFunctors();
    void wakeup();
    int createEventfd();


    ChannelList activeChanels;
    Channel *currentActiveChannel;

    pid_t threadId;
    bool looping;
    bool quit_;
    bool callingPendingFunctors;

    log LOG_DEBUG;
    std::unique_ptr<epoll> poll_;

    int wakeupFd;
    std::unique_ptr<Channel> weakupChannel;
    std::mutex Mutex;
    std::vector<Functor > pendingFunctions;
};

