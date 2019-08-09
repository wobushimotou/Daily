#pragma once
#include "TcpServer.h"
#include "EventLoop.h"
#include <fstream>

class HttpServer
{
public:
    HttpServer(EventLoop *loop,int port,std::string name);
    void start();

private:

    void onConnection(const TcpServer::TcpConnectionPtr &conn);
    void onMessage(const TcpServer::TcpConnectionPtr &conn,Buffer *buf,size_t);

    std::string onGet(std::string buff);
    TcpServer server;
};

