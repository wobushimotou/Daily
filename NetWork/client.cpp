#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include "chat.h"

using namespace std;

int main()
{
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd < 0) {
        cout << "套接字创建失败" << endl;
        exit(0);
    }

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(9527);

    int size = 0;
    int n;
    int sum = 0;
    
    socklen_t len = sizeof(size);    
         size = 0;
         getsockopt(fd,SOL_SOCKET,SO_RCVBUF,(void *)&size,&len);
         cout << "连接前接收缓冲区大小=" << size << endl;
 
    char buf[1000];
    int  connfd = socket(AF_INET,SOCK_STREAM,0);
    if(connect(connfd,(const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0) {
        /* write(connfd,buf,1); */
    }   
    size = 0;

         getsockopt(fd,SOL_SOCKET,SO_RCVBUF,(void *)&size,&len);
         cout << "连接后接收缓冲区大小=" << size << endl;

    sleep(1);
    cout << "sum  = " << sum << endl;
    close(connfd);
    return 0;
}

