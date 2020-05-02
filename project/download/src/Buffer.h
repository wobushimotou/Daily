#pragma once
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#define DEFAULTSIZE 1024
#define EXTENDRATIO 2
class Buffer
{
public:
    Buffer();
    ~Buffer();

    void handleRead();
    void handleWrite();
    size_t WriteFile(int fd,int seek);

private:
    int fd;
    char *data;
    char *ndata;
    unsigned int readable;//可读数据大小
    unsigned int writeable;//可写空间大小
    unsigned int size;      //缓冲区大小

    void extendSpace();
};

