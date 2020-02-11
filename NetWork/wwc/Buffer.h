#pragma once
#include <algorithm>
#include <vector>
#include <string.h>
#include <algorithm>
#include <string>
#include <iostream>

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
    size_t writeableBytes() const { return buffer_.size() - writeIndex;}
    size_t prependableBytes() const { return readIndex; }
    char *begin() { return &*buffer_.begin(); }
    char *beginWriten() { return begin()+writeIndex; }
    char *peek() { return begin() + readIndex; }

    size_t retrieveAsString(size_t len,std::string &buff);
    size_t retrieveAllAsString(std::string &buff);
    void retrieve(size_t len);
    void retrieveAll();

    void append(std::string msg);
    void append(const char *data,size_t len);
    Buffer *getPointer() { return this; }

private:
    std::vector<char> buffer_;
    size_t readIndex;
    size_t writeIndex;

};

