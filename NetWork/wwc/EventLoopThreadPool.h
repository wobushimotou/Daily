#pragma once
#include <vector>
#include <thread>
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
    static void run(EventLoopThreadPool*,int);
    EventLoop *getNextLoop();

private:
    EventLoop *baseLoop_;
    std::mutex Mutex;
    std::condition_variable Cond;
    bool start_;
    int numThreads_;
    std::vector<std::thread> threads;
    std::vector<EventLoop *> loops;
    int next_;
};

