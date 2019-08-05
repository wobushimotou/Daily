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

void TcpConnection::handleWrite()
{
    if(channel->isWriting()) {
        size_t n = ::write(channel->fd(),outputBuffer.peek(),outputBuffer.readableBytes());

        if(n > 0) {
            outputBuffer             
        }
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

void TcpConnection::sendInLoop(std::string message)
{
    size_t nworte = 0;
    if(!channel->isWriting() && outputBuffer.readableBytes() == 0) {
        nworte = ::write(socket->fd(),message.data(),message.size());
        if(nworte >= 0) {
            if(nworte < message.size()) {
                std::cout << "write more \n";
            }
        }
        else {
            nworte = 0;
        }
    }

    if(nworte < message.size()) {
        outputBuffer.append(message.data()+nworte,message.size()-nworte);
        if(!channel->isWriting())
            channel->enableWriting();
    }
}

void TcpConnection::send(std::string message)
{
    if(state == kConnected) {
        if(loop->isInLoopThread())
            sendInLoop(message);
        else {
            loop->runInLoop(std::bind(static_cast<void(TcpConnection::*)(std::string)>(&TcpConnection::sendInLoop),this,message));
        }
    }

}

void TcpConnection::shutdown()
{
    if(state == kConnected) {
        setState(kDisconnected);
        loop->runInLoop(std::bind(&TcpConnection::shutdownInLoop,this));
    }
}

void TcpConnection::shutdownInLoop()
{
    if(state == kConnected) {
        if(!channel->isWriting())
            socket->shutdown();
    }
}

