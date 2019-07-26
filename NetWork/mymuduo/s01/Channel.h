#pragma once
#include <boost/noncopyable.hpp>
#include <functional>
#include "../s00/EventLoop.h"
class Channel : boost::noncopyable
{
public:
    typedef std::function<void()> EventCallback;

    Channel(EventLoop *loop,int fd);
    void handleEvent();

    void setReadCallBack(const EventCallback& cb) { readCallBack_ = cb; }
    void setWriteCallBack(const EventCallback& cb) { writeCallBack_ = cb; }
    void setErrorCallBack(const EventCallback& cb) { errorCallBack_ = cb; }

    int fd() const { return fd_; }
    int events() const { return events_;}
    void set_revents(int revt) { revents_ = revt; }
    bool isNoneEvent() const { return events_ == kNoneEvent; }

    void enableReading() { events_ |= kReadEvent; update(); }
    /* void enableWriteing() { events_ |= kWriteEvent; update(); } */
    /* void disenableWriteing() { events_ &= ~kWriteEvent; update(); } */
    /* void disenableAll() { events_ = kNoneEvent; update(); } */
    ~Channel();

    // for Poller
    int index() { return index_; }
    void set_index(int idx) { index_ = idx; }
    
    EventLoop *ownerLoop() { return loop_; }
private:
    void update();

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_;
    const int fd_;
    int events_;
    int revents_;
    int index_;

    EventCallback readCallBack_;
    EventCallback writeCallBack_;
    EventCallback errorCallBack_;

};

