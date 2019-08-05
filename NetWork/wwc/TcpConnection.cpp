#include <iostream>
#include "TcpConnection.h"
void TcpConnection::handleRead()
{
    std::cout << "TcpConnection::handleRead()\n";
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
    :   socket(new Socket(sockfd)),
        loop(loop),
        name_(name),
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
    std::cout << "TcpConnection::handleClose()\n";
    channel->disableAll();    
    if(closeCallback)
        closeCallback(shared_from_this());
}

void TcpConnection::handleError()
{
    
}

void TcpConnection::connectDestoryed()
{
    channel->remove();
    socket->~Socket();
}

void TcpConnection::send(void *message,int len)
{
    send(std::string((char *)message));
}

void TcpConnection::send(std::string message)
{
    if(state == kConnected) {
        if(loop->isInLoopThread())
            sendInLoop(message);
        else {
        }
    }

}

void TcpConnection::sendInLoop(std::string message)
{

}

