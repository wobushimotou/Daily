#pragma once
#include <algorithm>
#include <vector>
#include <string.h>
#include <algorithm>
#include <string>
#include <iostream>
#include "./log/log.h"

class Buffer
{
public:
    static const size_t kCheapPrepend = 8;
    static const size_t kInitialSize = 1024;
    size_t readFd(int fd);
    Buffer(size_t Initsize = kInitialSize)
        :buffer_(Initsize),
        readIndex(kCheapPrepend),
        writeIndex(kCheapPrepend)
    {

    }
    size_t readableBytes() const { return writeIndex - readIndex;  }
    size_t writeableBytes() const { return buffer_.size() - writeIndex; }
    size_t prependableBytes() const { return readIndex; }
    char *begin() { return &*buffer_.begin(); }
    char *beginWriten() { return begin()+writeIndex; }
    char *peek() { return begin() + readIndex; }

    size_t retrieve(size_t len,std::string &buff);

    size_t retrieveAll(std::string &buff);
    ~Buffer();

private:
    std::vector<char> buffer_;
    size_t readIndex;
    size_t writeIndex;

};

