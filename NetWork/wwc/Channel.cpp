#include "Channel.h"
#include "EventLoop.h"
const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(std::shared_ptr<EventLoop> loop,int fd)
   :loop_(loop),
    fd_(fd),
    events_(0),
    revents_(0),
    index_(-1)
{
}

void Channel::update()
{
    loop_->updateChannel(this);    
}


void Channel::handleEvent()
{ 
    if(revents_ & POLLHUP && !(revents_ & POLLIN)) {
        if(closeCallback)
            closeCallback();
    }

    if(revents_ & (POLLERR | POLLNVAL)) {
        if(errorCallback) 
            errorCallback();
    }
    
    if(revents_ & (POLLIN | POLLPRI | POLLRDHUP)) {
        if(readCallback) {
            readCallback();
        }
    }
    
    if(revents_ & POLLOUT) {
        if(writeCallback)
            writeCallback();
    }
}


void Channel::remove()
{
    loop_->removeChannel(this);
}
