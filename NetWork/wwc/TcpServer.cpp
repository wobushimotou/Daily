#include <iostream>
#include "TcpServer.h"

TcpServer::TcpServer(EventLoop *loop,int port,std::string namearg)
    :loop(loop),
    name(namearg),
    acceptor(new Acceptor(loop,port)),
    connectionCallback(NULL),
    messageCallback(NULL),
    started(false),
    nextConnId(1)
{
    acceptor->setNewConnectionCallback(
        std::bind(&TcpServer::NewConnection,this,std::placeholders::_1,std::placeholders::_2));
    std::cout << "TcpServer()\n";
}

void TcpServer::NewConnection(int sockfd,struct sockaddr_in addr)
{
    std::cout << "TcpServer::NewConnection()\n";
    char buf[64];
    //为新创建的TcpConnection对象起名
    snprintf(buf,sizeof buf,"-%s#%d",inet_ntoa(addr.sin_addr),nextConnId);
    ++nextConnId;
    std::string connName = buf+name;
    TcpConnectionPtr conn(new TcpConnection(loop,connName,sockfd));

    connections[connName] = conn;
    conn->setConnectionCallback(connectionCallback);
    conn->setMessageCallback(messageCallback);
    conn->connectEstablished();
}



TcpServer::~TcpServer()
{

}

void TcpServer::start()
{
    loop->runInLoop(std::bind(&Acceptor::listen,acceptor.get()));
}

