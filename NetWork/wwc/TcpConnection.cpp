#include <iostream>
#include <signal.h>
#include "TcpConnection.h"

TcpConnection::TcpConnection(std::shared_ptr<EventLoop> loop,std::string &name,int sockfd)
    :   socket(new Socket(sockfd)),
        channel(new Channel(loop,sockfd)),
        loop(loop),
        name_(name)
{
    channel->setReadCallback( std::bind(&TcpConnection::handleRead,this));
    channel->setCloseCallback(std::bind(&TcpConnection::handleClose,this));
}


void TcpConnection::handleRead()
{
    printf("TcpConnection::handleRead\n");
    size_t n = inputBuffer.readFd(channel->fd());
    printf("n = %zd\n",n);
    if(n > 0) {    
        messageCallback(shared_from_this(),&inputBuffer,n);
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
            outputBuffer.retrieve(n);
            if(outputBuffer.readableBytes() == 0) {
                channel->disableAll();
                if(writeCompleteCallback_) {
                    loop->queueInLoop(std::bind(&TcpConnection::writeCompleteCallback_,shared_from_this()));
                }
                if(state == kDisconnected)
                    shutdownInLoop();
            }
        }
    }
}
void TcpConnection::connectEstablished()
{
    setState(kConnected);
    channel->enableReading();
    connectionCallback(shared_from_this());
}

TcpConnection::~TcpConnection()
{
    if(state != kDisconnected)
        connectDestoryed();
}


void TcpConnection::handleClose()
{
    channel->disableAll();    
    setState(kDisconnected);
    if(closeCallback)
        closeCallback(shared_from_this());
    
}

void TcpConnection::handleError()
{
    
}

void TcpConnection::connectDestoryed()
{
    channel->remove();
    socket->shutdown();
}

void TcpConnection::send(void *message,int len)
{
    send(std::string((char *)message));
}

void TcpConnection::sendInLoop(std::string message)
{
    
    size_t nworte = 0;
    if(!channel->isWriting() && outputBuffer.readableBytes() == 0) {
        nworte = ::send(socket->fd(),message.data(),message.size(),MSG_WAITALL);
        if(nworte >= 0) {
            if(nworte < message.size()) {
            }
        }
        else {
            perror("error nworte < 0\n");
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
        if(loop->isInLoopThread()) {
            sendInLoop(message);
        }
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

