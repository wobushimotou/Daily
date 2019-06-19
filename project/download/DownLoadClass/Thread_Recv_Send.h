#pragma once
#include <iostream>
#include <fstream>
#include <thread>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
struct AttriBute{
    long l_range;
    long r_range;
    long size;
    char pathname[100];
    char  buf[1000];
    AttriBute() = default;
    AttriBute(long lhs,long rhs) : l_range(lhs),r_range(rhs) {
        bzero(pathname,sizeof(pathname));
        bzero(buf,sizeof(buf));
    }
};

class Thread_Recv_Send {
public:
    //构造函数
    Thread_Recv_Send(const int _fd) : fd(_fd) {  } 
    ///发送文件
    int Send_File(const std::string &pathname);
    //接收文件
    int Recv_File(void);
    

    //析构函数
    ~Thread_Recv_Send()=default;

    friend void Thread_Send(long lhs,long rhs,const Thread_Recv_Send &t);
    friend void Thread_Recv(const AttriBute ab);
private:
    //线程发送/接收函数
    int fd;                 //使用的套接字
    std::string filename;       //文件名
    long size;
    int thread_num;         //线程数量
};

