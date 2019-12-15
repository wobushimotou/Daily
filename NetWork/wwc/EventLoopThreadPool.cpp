#include <iostream>
#include "EventLoopThreadPool.h"
EventLoopThreadPool::EventLoopThreadPool()
    :start_(false),
    numThreads_(1),
    loops(numThreads_),
    next_(0),
    distributions(numThreads_)
{
}

EventLoopThreadPool::EventLoopThreadPool(std::shared_ptr<EventLoop> baseloop)
    :baseLoop_(baseloop)
{
    EventLoop();
}

void EventLoopThreadPool::threadFun() {
    std::shared_ptr<EventLoop> loop = std::make_shared<EventLoop>();
    {
        Mutex.lock();
        loop_ = loop;
        Cond.notify_one();
        Mutex.unlock();
    }

    HttpServer server(loop,9999,"wang"); 
    server.start();

    loop->loop();
    
    Mutex.lock();
    loop_ = NULL;
    Mutex.unlock();
}

std::shared_ptr<EventLoop> EventLoopThreadPool::startLoop() {

    std::unique_lock<std::mutex> lck(Mutex,std::defer_lock);
    std::shared_ptr<EventLoop> loop = NULL;
    {
        Mutex.lock();
        /* while(loop_ == NULL) */
        Cond.wait(lck);
        loop = loop_;
        Mutex.unlock();
    }

    return loop;
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
        threads.emplace_back(std::bind(&EventLoopThreadPool::threadFun,this)); 
        loops[i] = startLoop();
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
    
    return p;
}

EventLoopThreadPool::~EventLoopThreadPool() {
    Cond.notify_all();

    for(std::thread &e:threads)
        e.join();
}
