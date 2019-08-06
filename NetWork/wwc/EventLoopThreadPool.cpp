#include <iostream>
#include "EventLoopThreadPool.h"
EventLoopThreadPool::EventLoopThreadPool(EventLoop *baseLoop)
    : baseLoop_(baseLoop),
    start_(false),
    next_(0),
    numThreads_(0)
{
}

void EventLoopThreadPool::setThreadNum(int numThreads)
{
    numThreads_ = numThreads;
}


void EventLoopThreadPool::start()
{
    start_ = true;
    for(int i = 0;i != numThreads_;++i) {
        
    }

}


