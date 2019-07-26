#include "Channel.h"
const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop *loop,int fdArg)
    :loop_(loop),
    fd_(fdArg),
    events_(0),
    revents_(0),
    index_(-1)
{

}

void Channel::update() {
    loop_->updateChannel(this);
}

void Channel::handleEvent() {
    if(revents_ & POLLNVAL) {
        std::cout << "Channel::handle_event() POLLNVAL";
    }

    if(revents_ & (POLLERR | POLLNVAL)) {
        if(errorCallBack_)
            errorCallBack_();
    }

    if(revents_ & (POLLIN | POLLPRI | POLLRDHUP)) {
        if(readCallBack_)
            readCallBack_();
    }

    if(revents_ & POLLOUT) {
        if(writeCallBack_)
            writeCallBack_();
    }
}
