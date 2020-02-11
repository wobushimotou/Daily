#pragma once
#include <netinet/in.h>
#include <arpa/inet.h>
#include <functional>
#include "./EventLoop.h"
#include "./Socket.h"
class InetAddress;
class Acceptor
{
public:
    typedef std::function<void (int sockfd,struct sockaddr_in addr)> NewConnectionCallback;
    Acceptor(std::shared_ptr<EventLoop> loop,int port);
    ~Acceptor();

    void setNewConnectionCallback(const NewConnectionCallback& cb) { newConnectionCallback_ = cb; }
    bool listening() const { return listening_; }
    void listen();

private:
    void handleRead();  //处理连接事件
    void initAddr();

    std::shared_ptr<EventLoop> loop;
    Socket acceptSocket;
    Channel acceptChannel;
    int port;
    struct sockaddr_in addr;
    NewConnectionCallback newConnectionCallback_;
    bool listening_;
    int sock;
};

