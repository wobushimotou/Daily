#pragma once
#include <sys/epoll.h>
#include <vector>
#include <map>
#include "../EventLoop.h"
#include "../Channel.h"
class EventLoop;
class Channel;

/*
 *  IO多路复用之epoll的封装 
 * */
class epoll
{
public:

    typedef std::vector<Channel*> ChannelList;
    epoll(EventLoop *loop);
    ~epoll();

    int poll(int timeoutMs,ChannelList *activeChannels);

    void updateChannel(Channel *channel);
    void removeChannel(Channel *channel);
    void update(int operation,Channel *channel);
    
    void assertInLoopThread();
private:
    void fillActiveChannels(int numEvents,ChannelList *activeChannels);
    typedef std::vector<struct epoll_event> EPollList;
    typedef std::map<int,Channel*> ChannelMap;

    EventLoop *ownerLoop;
    ChannelMap channels;
    EPollList events;
    int epollfd;
};

