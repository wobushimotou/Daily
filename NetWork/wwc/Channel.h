#pragma once
#include "./log/log.h"
#include <functional>
class EventLoop;

class Channel
{
public:
    typedef std::function<void()> EventCallback;
    Channel(EventLoop *loop,int fd);
    ~Channel() {}

    void handleEvent();
    void setReadCallback(const EventCallback &cb) { readCallback = cb; }
    void setWriteCallback(const EventCallback &cb) { writeCallback = cb; }
    void setErrorCallback(const EventCallback &cb) { errorCallback = cb; }
    void setCloseCallback(const EventCallback &cb) { closeCallback = cb; }

    int fd() { return fd_; }
    int events() { return events_;}
    void set_revents(int retv) { revents_ = retv; }
    bool isNoneEvnet() { return events_ == kNoneEvent; }

    void enableReading() { events_ |= kReadEvent; update(); }
    void disableAll() { events_ |= kNoneEvent; update(); }

    int index() { return index_; }
    void set_index(int idx) { index_ = idx; }

    EventLoop *ownLoop() { return loop_; }
private:
    void update();

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_;
    int fd_;
    int events_;
    int revents_;
    int index_;     //存储在epoll::events数组中的位置
    log LOG_DEBUG;

    EventCallback readCallback;
    EventCallback writeCallback;
    EventCallback errorCallback;
    EventCallback closeCallback;
};
