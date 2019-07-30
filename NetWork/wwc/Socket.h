#pragma once
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
class Socket
{
public:
    Socket();
    ~Socket();

private:
    int sockfd;
};

