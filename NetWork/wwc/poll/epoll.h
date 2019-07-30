#pragma once
#include <sys/epoll.h>
#include <vector>
#include <map>
#include "../log/log.h"
#include "../EventLoop.h"
#include "../Channel.h"
/*
 *  IO多路复用之epoll的封装 
 * */
class epoll
{
public:

    typedef std::vector<Channel *> ChannelList;
    epoll(EventLoop *loop);
    ~epoll();

    int poll(int timeoutMs,ChannelList *activeChannels);

    void updateChannel(Channel *channel);
    
    void assertInLoopThread();
private:
    void fillActiveChannels(int numEvents,ChannelList *activeChannels);
    typedef std::vector<struct epoll_event> EPollList;
    typedef std::map<int,Channel*> ChannelMap;

    EventLoop *ownerLoop;
    EPollList events;
    ChannelMap channels;
    int epollfd;
    log LOG_DEBUG;
};

