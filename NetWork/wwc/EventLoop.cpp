#include "EventLoop.h"
EventLoop::EventLoop()
    :threadId(syscall(SYS_gettid)),
    looping(false),
    eventHanding(false),
    poll_(new epoll(this)),
    wakeupFd(createEventfd()),
    weakupChannel(new Channel(this,wakeupFd))
{
}


EventLoop::~EventLoop()
{
    if(looping)
        ;
}
void EventLoop::loop()
{
    if(!isInLoopThread()) {
        exit(0);
    }

    looping = true;
    quit_ = false;
    while(!quit_) {
        activeChanels.clear();
        poll_->poll(1000,&activeChanels);
        eventHanding = true;

        for(auto p = activeChanels.begin();p != activeChanels.end();++p) {
            (*p)->handleEvent();
        }

        eventHanding = false;
        doPendingFunctors();
    }
    looping = false;
}


void EventLoop::updateChannel(Channel *channel)
{
    std::cout << "EventLoop::updateChannel()\n";
    poll_->updateChannel(channel);
}

void EventLoop::quit()
{
    quit_ = true;
}

void EventLoop::runInLoop(const Functor &cb)
{
    if(isInLoopThread()) {
        cb();
    }
    else {
        queueInLoop(cb);        
    }
}

void EventLoop::queueInLoop(const Functor &cb)
{
    Mutex.lock();
    pendingFunctions.push_back(cb);
    Mutex.unlock();
    if(!isInLoopThread() || callingPendingFunctors) {
        wakeup();
    }
}

void EventLoop::doPendingFunctors()
{
    std::vector<Functor> functors;
    callingPendingFunctors = true;

    Mutex.lock();
    functors.swap(pendingFunctions);
    Mutex.unlock();

    for(size_t i = 0;i < functors.size();++i)
        functors[i]();

    callingPendingFunctors = false;
}

void EventLoop::wakeup()
{
    char ch;
    size_t n = ::write(wakeupFd,&ch,1);
    if(n != sizeof ch) {
    }
}

void EventLoop::handleRead() {
    char ch;
    size_t n = ::read(wakeupFd,&ch,1);
    if(n != sizeof ch) {
    }
}

int EventLoop::createEventfd() {
    int evfd = ::eventfd(0,EFD_NONBLOCK | EFD_CLOEXEC);
    if(evfd < 0) {
    }
    return evfd;
}
void EventLoop::removeChannel(Channel *channel)
{
    if(eventHanding)
        assert(currentActiveChannel == channel || 
           std::find(std::begin(activeChanels),std::end(activeChanels),channel) == activeChanels.end());

    poll_->removeChannel(channel);
}

