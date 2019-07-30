#include "Socket.h"
Socket::Socket()
{
    sockfd = socket(AF_INET,SOCK_STREAM,0);    
}

