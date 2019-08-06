#pragma once
#include <vector>
#include <mutex>
#include <condition_variable>
#include "EventLoop.h"
class EventLoopThreadPool
{
public:
    EventLoopThreadPool(EventLoop *baseLoop);
    ~EventLoopThreadPool();
    void setThreadNum(int numThreads);
    void start();
    EventLoop *getNextLoop();

private:
    EventLoop *baseLoop_;
    std::mutex Mutex;
    std::condition_variable Cond;
    bool start_;
    int next_;
    int numThreads_;
    std::vector<EventLoop*> loops;
};

