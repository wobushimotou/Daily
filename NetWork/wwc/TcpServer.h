#pragma once
#include <functional>
#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"

class TcpConnection;
class TcpServer
{
public:
    typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
    typedef std::function<void (std::shared_ptr<TcpConnection>)> ConnectionCallback;
    typedef std::function<void (std::shared_ptr<TcpConnection>,char *,size_t)> MessageCallback;

    TcpServer(EventLoop *loop,int port,std::string namearg);
    ~TcpServer();

    void start();

    void setConnectionCallback(const ConnectionCallback &cb) {
        connectionCallback = cb;
    }
    void setMessageCallback(const MessageCallback &cb) {
        messageCallback = cb;
    }

private:
    
    void NewConnection(int sockfd,struct sockaddr_in addr);
    typedef std::map<std::string,TcpConnectionPtr> ConnectionMap;

    EventLoop *loop;
    std::string name;
    std::unique_ptr<Acceptor> acceptor;
    ConnectionCallback connectionCallback;
    MessageCallback messageCallback;
    bool started;
    int nextConnId;
    ConnectionMap connections;

};

