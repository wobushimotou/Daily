#include <iostream>
#include "EventLoopThreadPool.h"
EventLoopThreadPool::EventLoopThreadPool(EventLoop *baseLoop)
    : baseLoop_(baseLoop),
    start_(false),
    numThreads_(10),
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

        loops[i] = std::make_shared<EventLoop>();
        threads.emplace_back(run,this,i);
        /* threads[i].detach(); */ 
    }
}

std::shared_ptr<EventLoop> EventLoopThreadPool::getNextLoop() {

    auto p = baseLoop_;
    int n = 0;
    if(!loops.empty()) {
        n = next_++;
        if(static_cast<size_t>(next_) >= loops.size()) {
            next_ = 0;
        }
        p = loops[n];
    }
    

    /* int flag = 1; */
    /* for(int i = 0;i != numThreads_;++i) */
    /*     if(loops[i].get() == loop) { */
    /*         printf("i = %d\n",i); */
    /*         flag = 0; */
    /*     } */
    /* if(flag) */
    /*     printf("loop alone\n"); */

    
    return p;
}

EventLoopThreadPool::~EventLoopThreadPool()
{
   Cond.notify_all();

   for(std::thread &e:threads)
       e.join();
}
