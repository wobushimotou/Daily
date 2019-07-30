#include "epoll.h"
epoll::epoll(EventLoop *loop) 
    : ownerLoop(loop),epollfd(epoll_create(1)) {

}

epoll::~epoll() {

}

int epoll::poll(int timeoutMs,ChannelList *activeChannels)
{
    int numEvents = epoll_wait(epollfd,&*events.begin(),events.size(),timeoutMs);

    if(numEvents < 0) {
        LOG_DEBUG << "numEvents < 0";
        return numEvents;
    }
    else if(numEvents == 0) {
        //超时,不处理
    }
    else {
        fillActiveChannels(numEvents,activeChannels);

    }
    return numEvents;
    
}


void epoll::fillActiveChannels(int numEvents,ChannelList *activeChannels)
{
    for(int i = 0;i < numEvents;++i) {
        Channel *channel = static_cast<Channel *>(events[i].data.ptr);
        int fd = channel->fd();
        auto it = channels.find(fd);
        if(it == channels.end()) {
            LOG_DEBUG << std::string("find fd in map<fd,Channel*> error\n");
            continue;
        }
        channel->set_revents(events[i].events);
        activeChannels->push_back(channel);
    }
    
}

void epoll::updateChannel(Channel *channel)
{
    int index = channel->index();
    if(index < 0) {
        //添加新的事件分发器

    }
    else {
        //更新现有的时间分发器
        
    }
}

