#include "epoll.h"
epoll::epoll(EventLoop *loop) 
    : ownerLoop(loop),epollfd(epoll_create(1)){
    events.resize(16);
}

epoll::~epoll() {

}

int epoll::poll(int timeoutMs,ChannelList *activeChannels)
{
    int numEvents = epoll_wait(epollfd,&*events.begin(),events.size(),timeoutMs);

    if(numEvents < 0) {
        return numEvents;
    }
    else if(numEvents == 0) {
        //超时,不处理
    }
    else {
        fillActiveChannels(numEvents,activeChannels);
        if(numEvents == static_cast<int>(events.size())) {
            events.resize(2*numEvents);
        }
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
    std::cout << "epoll updateChannel()\n";
    int index = channel->index();
    if(index < 0) {
        std::cout << "添加新的事件分发器\n";
        //添加新的事件分发器
        index = events.size(); 
        channel->set_index(index);
        channels[channel->fd()] = channel;
        update(EPOLL_CTL_ADD,channel);
   }
    else {
        std::cout << "更新现有的时间分发器\n";
        //更新现有的时间分发器
        struct epoll_event event;
        event.events = channel->events();
        if(channel->isNoneEvnet()) {
            update(EPOLL_CTL_DEL,channel);
            channel->set_index(-1);

        }else {
            update(EPOLL_CTL_ADD,channel);
        }

    }
}

void epoll::update(int operation,Channel *channel)
{
    struct epoll_event event;
    event.events = channel->events();
    if(channel->events() & POLLIN)
        std::cout << "update() POLLIN\n";
    else if(channel->events() & POLLOUT)
        std::cout << "update() POLLOUT\n";
    else 
        std::cout << "update() ERROR\n";

    event.data.ptr = static_cast<void *>(channel);

    if(epoll_ctl(epollfd,operation,channel->fd(),&event) < 0) {
        LOG_DEBUG << "update channel error\n"; 
    }

}
