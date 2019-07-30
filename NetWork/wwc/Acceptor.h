#pragma once
#include <netinet/in.h>
#include <functional>
#include "./EventLoop.h"
class InetAddress;
class Acceptor
{
public:
    typedef std::function<void (int sockfd,struct sockaddr addr)> NewConnectionCallback;
    Acceptor(EventLoop *loop,struct sockaddr listenaddr);
    ~Acceptor();

    void setNewConnectionCallback(const NewConnectionCallback& cb) { newConnectionCallback_ = cb; }
    bool listening() const { return listening_; }
    void listen();

private:
    void handleRead();

    EventLoop *loop;
    int acceptSocket;
    Channel acceptChannel;
    NewConnectionCallback newConnectionCallback_;
    bool listening_;
};

