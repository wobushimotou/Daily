#pragma once
#include <netinet/in.h>
#include <functional>
#include "./EventLoop.h"
#include "./Socket.h"
class InetAddress;
class Acceptor
{
public:
    typedef std::function<void (int sockfd,struct sockaddr addr)> NewConnectionCallback;
    Acceptor(EventLoop *loop,std::string sockaddr);
    ~Acceptor();

    void setNewConnectionCallback(const NewConnectionCallback& cb) { newConnectionCallback_ = cb; }
    bool listening() const { return listening_; }
    void listen();

private:
    void handleRead();

    EventLoop *loop;
    Socket acceptSocket;
    Channel acceptChannel;
    struct sockaddr addr;
    NewConnectionCallback newConnectionCallback_;
    bool listening_;
};

