#include <iostream>
#include "TcpConnection.h"
void TcpConnection::handleRead()
{
    size_t n = inputBuffer.readFd(channel->fd());
    if(n > 0) {
        messageCallback(shared_from_this(),inputBuffer,n);
    }
    else if(n == 0) {
        handleClose();
    }
    else {
        handleError();
    }
}

TcpConnection::TcpConnection(EventLoop *loop,std::string &name,int sockfd)
    :   loop(loop),
        name_(name),
        socket(new Socket(sockfd)),
        channel(new Channel(loop,sockfd))
{
    channel->setReadCallback( std::bind(&TcpConnection::handleRead,this));
    channel->setCloseCallback(std::bind(&TcpConnection::handleClose,this));
}

void TcpConnection::connectEstablished()
{
    setState(kConnected);
    channel->enableReading();
    
    connectionCallback(shared_from_this());
}

TcpConnection::~TcpConnection()
{

}


void TcpConnection::handleClose()
{
    channel->disableAll();    
    if(closeCallback)
        closeCallback(shared_from_this());
}

void TcpConnection::handleError()
{
    
}

void TcpConnection::connectDestoryed()
{
    setState(kDisconnected);
    channel->disableAll();
    connectionCallback(shared_from_this());

    loop->removeChannel(channel.get());
}

