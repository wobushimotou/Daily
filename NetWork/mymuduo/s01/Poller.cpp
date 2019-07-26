#include "Poller.h"

Poller::Poller(EventLoop *loop)
    :ownerLoop_(loop)
{

}
Poller::~Poller() {

}

int Poller::poll(int timeoutMs,ChannelList *activeChannels) {
    int numEvents = ::poll(&*pollfds_.begin(),pollfds_.size(),timeoutMs);
    if(numEvents > 0) {
        std::cout << numEvents << "events happened";
        fillActiveChannels(numEvents,activeChannels);
    }
    else if(numEvents == 0) {
        std::cout << "nothing happened";
    }
    else {
        std::cout << "Poller::poll()";
    }
    return numEvents;
}
