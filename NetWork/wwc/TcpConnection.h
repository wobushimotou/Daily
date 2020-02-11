#pragma once
#include <boost/noncopyable.hpp>
#include <functional>
#include <algorithm>
#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"
#include "Buffer.h"
class TcpConnection :   boost::noncopyable,
                        public std::enable_shared_from_this<TcpConnection>
{
public: 
    typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
    typedef Buffer * BufferPtr;
    typedef std::function<void(std::shared_ptr<TcpConnection>)> ConnectionCallback;
    typedef std::function<void(const TcpConnectionPtr&,BufferPtr,size_t)> MessageCallback;
    typedef std::function<void (const TcpConnectionPtr&)> CloseCallback;
    typedef std::function<void (const TcpConnectionPtr&)> writeCompleteCallback;


    void setConnectionCallback(const ConnectionCallback &cb) {
        connectionCallback = cb;
    }
    void setMessageCallback(const MessageCallback &cb) {
        messageCallback = cb;
    }
    void setCloseCallback(const CloseCallback& cb) {
        closeCallback = cb;
    }
    void setwriteCompleteCallback(const writeCompleteCallback &cb) {
        writeCompleteCallback_ = cb;
    }
    void setContext(void *context) {
        context_ = context;
    }
    bool connected() { return state == kConnected; }
    void send(void *message,int len);
    void send(std::string message);
    void send(Buffer *message);
    std::shared_ptr<EventLoop> getLoop() { return loop; }
    void connectEstablished();
    void connectDestoryed();
    std::string name() { return name_; }
    

    TcpConnection(std::shared_ptr<EventLoop> loop,std::string &name,int sockfd);
    ~TcpConnection();
    
    std::unique_ptr<Socket> socket;


    std::unique_ptr<Channel> channel;
private:
    enum StateE{kConnecting,kConnected,kDisconnected};

    void setState(StateE s) { state = s; }
    void handleRead();
    void handleWrite();
    void handleClose();
    void handleError();

    void sendInLoop(std::string message);
    void sendInLoop(void *message,int len);
    void shutdownInLoop();
    void shutdown();
    
    std::shared_ptr<EventLoop> loop;
    StateE state;
    void *context_;
    
    std::string name_;
    ConnectionCallback connectionCallback;
    MessageCallback messageCallback;
    CloseCallback closeCallback;
    writeCompleteCallback writeCompleteCallback_;
    Buffer inputBuffer;
    Buffer outputBuffer;
};

