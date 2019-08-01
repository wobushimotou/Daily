#include <iostream>
#include "TcpConnection.h"
void TcpConnection::handleRead()
{
    std::cout << "TcpConnection::handleRead()\n";
    char buf[65535];
    bzero(buf,65535);
    size_t n = ::read(channel->fd(),buf,sizeof buf);
    messageCallback(shared_from_this(),buf,n);
}

TcpConnection::TcpConnection(EventLoop *loop,std::string &name,int sockfd)
    :   loop(loop),
        name_(name),
        socket(new Socket(sockfd)),
        channel(new Channel(loop,sockfd))
{
    std::cout << "TcpConnection()\n";
    channel->setReadCallback( std::bind(&TcpConnection::handleRead,this));
}

void TcpConnection::connectEstablished()
{
    std::cout << "TcpConnection::connectEstablished()\n";
    setState(kConnected);
    channel->enableReading();
    
    std::cout << "TcpConnection::connectEstablished()->connectionCallback(this)\n";
    connectionCallback(shared_from_this());
    std::cout << "1\n";
}

TcpConnection::~TcpConnection()
{

}

