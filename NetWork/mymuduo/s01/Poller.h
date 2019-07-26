#pragma once
#include <boost/noncopyable.hpp>
#include <vector>
#include <map>
#include "Channel.h"
#include <poll.h>

class Poller
{
public:
    typedef std::vector<Channel *> ChannelList;
    Poller(EventLoop *loop);
    ~Poller();

    int poll(int timeoutMs,ChannelList* activeChannels);

    void updateChannel(Channel * channel);

    void assertInLoopThread() { ownerLoop_->assertInLoopThread(); }

private:
    void fillActiveChannels(int numEvents,ChannelList *activeChannels) const;

    typedef std::vector<struct pollfd> PollFdList;
    typedef std::map<int,Channel*> ChannelMap;

    EventLoop *ownerLoop_;
    PollFdList pollfds_;
    ChannelMap channels_;
};

