#include <iostream>
#include "EventLoopThreadPool.h"
EventLoopThreadPool::EventLoopThreadPool(EventLoop *baseLoop)
    : baseLoop_(baseLoop),
    start_(false),
    numThreads_(0),
    loops(1),
    next_(0)
{
    printf("EventLoopThreadPool::this = %p\n",this);
}
void EventLoopThreadPool::run(EventLoopThreadPool *t,int i) {
    printf("EventLoopThreadPool::run() %p\n",t);
    std::unique_lock<std::mutex> lock(t->Mutex);
    t->Cond.wait(lock);
    EventLoop *loop = new EventLoop();; 
    t->loops[i] = loop;
    t->next_ = i;
    lock.unlock();
}
void EventLoopThreadPool::setThreadNum(int numThreads)
{
    numThreads_ = numThreads;
    loops.resize(numThreads_+1);
}


void EventLoopThreadPool::start()
{
    start_ = true;
    if(numThreads_ == 0)
        loops[0] = baseLoop_;
    for(int i = 1;i <= numThreads_;++i) {
        threads.emplace_back(run,this,i);
    }

}

EventLoop *EventLoopThreadPool::getNextLoop() {

    std::unique_lock<std::mutex> lock(Mutex);
    if(numThreads_ >= 1) {
        Cond.notify_one();
    }
    lock.unlock();
    sleep(1);
    lock.lock();

    int i;

    if(numThreads_ == 0) {
        i = 0;
    }
    else 
        i = ++next_%numThreads_;

    lock.unlock();
    return loops[i];
}

EventLoopThreadPool::~EventLoopThreadPool()
{
   Cond.notify_all();

   for(std::thread &e:threads)
       e.join();
    
}

