#pragma once
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"
class TcpConnection :   boost::noncopyable,
                        public std::enable_shared_from_this<TcpConnection>
{
public: 
    typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
    typedef std::function<void(std::shared_ptr<TcpConnection>)> ConnectionCallback;
    typedef std::function<void(std::shared_ptr<TcpConnection>,char *,size_t)> MessageCallback;
    typedef std::function<void (const TcpConnectionPtr&)> CloseCallback;


    void setConnectionCallback(const ConnectionCallback &cb) {
        connectionCallback = cb;
    }
    void setMessageCallback(const MessageCallback &cb) {
        messageCallback = cb;
    }
    void setCloseCallback(const CloseCallback& cb) {
        closeCallback = cb;
    }
    void connectEstablished();
    void connectDestoryed();
    std::string name() { return name_; }
    TcpConnection(EventLoop *loop,std::string &name,int sockfd);
    ~TcpConnection();

private:
       enum StateE{kConnecting,kConnected};

    void setState(StateE s) { state = s; }
    void handleRead();
    void hanleWrite();
    void hanleClose();
    void handleError();
    
    EventLoop *loop;
    std::string name_;
    StateE state;

    std::unique_ptr<Socket> socket;
    std::unique_ptr<Channel> channel;
    
    ConnectionCallback connectionCallback;
    MessageCallback messageCallback;
    CloseCallback closeCallback;
};

