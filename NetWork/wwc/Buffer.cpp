#include <iostream>
#include <unistd.h>
#include "Buffer.h"
size_t Buffer::readFd(int fd)
{
    char extrabuf[65535];     
    bzero(extrabuf,65535);
    size_t writable = writeableBytes();
    size_t n = read(fd,extrabuf,65535);
    if(n < 0) {

    }
    else if(n <= writable) {
        std::copy(extrabuf,extrabuf+n,beginWriten());
        writeIndex += n;
    }
    else {
        buffer_.resize(buffer_.size()+n-writable);
        std::copy(extrabuf,extrabuf+n-writable,beginWriten());
        writeIndex += n;
    }
    
    return n;
}

size_t Buffer::retrieve(size_t len,std::string &buff)
{
        if(len < readableBytes()) {
            readIndex += len;
            if(buff.size() < len)
                buff.resize(len);
            
            std::copy(peek(),peek()+len,buff.begin());
            readIndex += len;
            return len;
        }
        else {
            return retrieveAll(buff);
        }
 
}

size_t Buffer::retrieveAll(std::string &buff)
{
    size_t len = readableBytes(); 
        if(buff.size() < len) 
            buff.resize(len);
        std::copy(peek(),peek()+len,buff.begin());
        readIndex += len;
        return len;
}

Buffer::~Buffer()
{

}

