#pragma once
#include "TcpServer.h"
#include "EventLoop.h"
#include <fstream>

class HttpServer
{
public:
    HttpServer(std::shared_ptr<EventLoop> loop,int port,std::string name);
    void start();

private:
    void onConnection(const TcpServer::TcpConnectionPtr &conn);
    void onMessage(const TcpServer::TcpConnectionPtr &conn,TcpConnection::BufferPtr buf,size_t);
    int ReadFile(std::string filename);
    void doGet(const TcpServer::TcpConnectionPtr &conn,std::string head);

    std::string onGet(std::string buff);
    TcpServer server;
    int clientnum;
    std::map<std::string,std::string> data;
};

