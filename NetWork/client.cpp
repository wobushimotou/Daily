#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>

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
    servaddr.sin_port = htons(5678);

    int size = 0;
    socklen_t len = sizeof(size);
    getsockopt(fd,IPPROTO_TCP,TCP_MAXSEG,(void *)&size,&len);
    cout << "连接前mss大小=" << size << endl;
    size = 0;

    getsockopt(fd,SOL_SOCKET,SO_RCVBUF,(void *)&size,&len);
    cout << "连接前接收缓冲区大小=" << size << endl;


    if(connect(fd,(const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0) {
        cout << "连接失败" << endl;
        exit(0);
    }
    size = 0;
    getsockopt(fd,IPPROTO_TCP,TCP_MAXSEG,(void *)&size,&len);
    cout << "连接后mss大小="<< size << endl;

    size = 0;
    getsockopt(fd,SOL_SOCKET,SO_RCVBUF,(void *)&size,&len);
    cout << "连接后接收缓冲区大小=" << size << endl;



    //setsockopt(fd,SOL_SOCKET,SO_LINGER)

    char ch;
    while(cin >> ch) {
        send(fd,&ch,1,0);
        if(recv(fd,&ch,1,0) > 0)
            cout << ch << endl;
        break;
    }
    close(fd);
    
    return 0;
}

