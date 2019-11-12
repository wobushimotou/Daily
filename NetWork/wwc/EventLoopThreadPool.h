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
    std::shared_ptr<EventLoop> getNextLoop();

private:
    std::shared_ptr<EventLoop> baseLoop_;
    std::mutex Mutex;
    std::condition_variable Cond;
    bool start_;
    int numThreads_;
    std::vector<std::thread> threads;
    std::vector<std::shared_ptr<EventLoop>> loops;
    int next_;
    int distributions;
};

