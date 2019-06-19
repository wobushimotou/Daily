#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

using namespace std;

int main()
{
    int fd = socket(AF_INET,SOCK_STREAM,0);
    int size;
    int maxsize;
    socklen_t len = sizeof(size);
    getsockopt(fd,SOL_SOCKET,SO_RCVBUF,(void *)&size,&len);
    cout << size << endl;

    getsockopt(fd,IPPROTO_TCP,TCP_MAXSEG,(void *)&maxsize,&len);
    cout << maxsize << endl;
    return 0;
}

