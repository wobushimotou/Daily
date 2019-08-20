#pragma once
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <string.h>
class Socket
{
public:
    Socket();
    Socket(int fd);
    ~Socket();
    int fd() const { return sockfd; }
    void bindAddress(struct sockaddr_in addr);
    void SetNonblock();
    void listenAddr(); 
    int acceptAddr(struct sockaddr_in *addr);
    struct sockaddr_in GetLocalAddr();
    void shutdown();
private:
    int sockfd;
};

