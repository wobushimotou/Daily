#pragma once
#include <functional>
#include "EventLoop.h"
class EventLoop;
class Channel
{
public:
    typedef std::function<void()> EventCallback;
    Channel(std::shared_ptr<EventLoop> loop,int fd);
    
    ~Channel() {  }

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
    void enableWriting() { events_ |= kWriteEvent; update(); }
    void disableReading() { events_ &= ~kReadEvent;update();}
    void disableWriting() { events_ &= ~kWriteEvent;update();}
    void disableAll() { events_ = kNoneEvent; update(); }
    bool isWriting() const { return events_ & kWriteEvent; }

    int index() { return index_; }
    void set_index(int idx) { index_ = idx; }

    std::shared_ptr<EventLoop> ownLoop() { return loop_; }
    void remove();
    void shutdown();
private:
    void update();

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    std::shared_ptr<EventLoop> loop_;
    int fd_;
    int events_;
    int revents_;
    int index_;     //存储在epoll::events数组中的位置

    EventCallback readCallback;
    EventCallback writeCallback;
    EventCallback errorCallback;
    EventCallback closeCallback;
};
