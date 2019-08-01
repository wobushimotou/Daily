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
    loop_->updateChannel(this);    
}


void Channel::handleEvent()
{
    if(revents_ & POLLNVAL) {
        LOG_DEBUG << "Channel::handle_event() POLLNVAL\n";
    }

    if((revents_ & POLLHUP) && !(revents_ & POLLIN)) {
        if(closeCallback)
            closeCallback();
    }

    if(revents_ & POLLERR) {
        if(errorCallback) 
            errorCallback();
    }
    
    if(revents_ & POLLIN) {
        if(readCallback) {
            readCallback();
        }
    }
    
    if(revents_ & POLLOUT) {
        if(writeCallback)
            writeCallback();
    }
}


