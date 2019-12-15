#include "epoll.h"
epoll::epoll(EventLoop *loop) 
    : ownerLoop(loop),epollfd(epoll_create(1))
{
    events.resize(16);
}

epoll::~epoll() {
}

int epoll::poll(int timeoutMs,ChannelList *activeChannels)
{

    int numEvents = epoll_wait(epollfd,&*events.begin(),events.size(),timeoutMs);

    if(numEvents < 0) {
        return -1;
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
        index = events.size(); 
        channel->set_index(index);
        channels[channel->fd()] = channel;
        update(EPOLL_CTL_ADD,channel);
    }
    else {
        //更新现有的时间分发器
        if(channel->isNoneEvnet()) {
            update(EPOLL_CTL_DEL,channel);
            channel->set_index(-1);
        }
        else {
            update(EPOLL_CTL_MOD,channel);
        }

    }
}

void epoll::update(int operation,Channel *channel)
{
    struct epoll_event event;
    event.events = channel->events();
    event.data.ptr = channel;
    int fd = channel->fd();

    if(epoll_ctl(epollfd,operation,fd,&event) < 0) {
        if(operation == EPOLL_CTL_DEL) {
            switch(errno) {
            case EBADE:
                break;
            case EINVAL:
                break;
            case ENOENT:
                if(close(fd) == 0) {
                }
                else
                break;
            case ENOMEM:
                break;
            case EEXIST:
                break;
            case EPERM:
                break;
            }


        }
    }
}

void epoll::removeChannel(Channel *channel)
{
    int fd = channel->fd();
    size_t n = channels.erase(fd);
    /* assert(n == 1); */
    update(EPOLL_CTL_DEL,channel);
}

