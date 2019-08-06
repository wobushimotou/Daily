#include "Channel.h"
#include "EventLoop.h"
const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop *loop,int fd)
   :loop_(loop),
    fd_(fd),
    events_(0),
    revents_(0),
    index_(-1)
{
}

void Channel::update()
{
    std::cout << "Channel::update()\n";
    loop_->updateChannel(this);    
}


void Channel::handleEvent()
{ 
    std::cout << "Channel::handleEvent()\n";
    if(revents_ & POLLNVAL) {
        LOG_DEBUG << "Channel::handle_event() POLLNVAL\n";
    }

    if(revents_ & POLLHUP) {
        std::cout << "Channel::closeCallback\n";
        if(closeCallback)
            closeCallback();
    }

    if(revents_ & POLLERR) {
        std::cout << "Channel::errorCallback\n";
        if(errorCallback) 
            errorCallback();
    }
    
    if(revents_ & POLLIN) {
        std::cout << "Channel::readCallback\n";
        if(readCallback) {
            readCallback();
        }
    }
    
    if(revents_ & POLLOUT) {
        std::cout << "Channel::writeCallback\n";
        if(writeCallback)
            writeCallback();
    }
}


void Channel::remove()
{
    loop_->removeChannel(this);
}

