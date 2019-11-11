#include <iostream>
#include "EventLoopThreadPool.h"
EventLoopThreadPool::EventLoopThreadPool(EventLoop *baseLoop)
    : baseLoop_(baseLoop),
    start_(false),
    numThreads_(3),
    loops(numThreads_),
    next_(0),
    distributions(numThreads_)
{
}
void EventLoopThreadPool::run(EventLoopThreadPool *t,int i) {
    t->loops[i]->loop();
}

void EventLoopThreadPool::setThreadNum(int numThreads)
{
    numThreads_ = numThreads;
    distributions = numThreads;
    loops.resize(numThreads_);
}

void EventLoopThreadPool::start()
{
    start_ = true;
    for(int i = 0;i < numThreads_;++i) {
        EventLoop *ioLoop = new EventLoop();
        loops[i] = ioLoop;
        threads.emplace_back(run,this,i);
        threads[i].detach(); 
    }
}

EventLoop *EventLoopThreadPool::getNextLoop() {

    EventLoop *loop = baseLoop_;

    if(!loops.empty()) {
        loop = loops[next_];
        ++next_;
        if(static_cast<size_t>(next_) >= loops.size()) {
            next_ = 0;
        }
    }
    return loop;
}

EventLoopThreadPool::~EventLoopThreadPool()
{
   Cond.notify_all();

   for(std::thread &e:threads)
       e.join();
}

